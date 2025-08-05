#!/usr/bin/env python3
"""
C++ Hot Reload System using Ninja Build System

This script provides automatic rebuilding and execution of C++ projects
when source files change, similar to hot reload in web development.

Usage:
    python hot_reload.py [options]

Features:
    - Watches C++ source files for changes
    - Automatically triggers Ninja builds
    - Shows exactly what Ninja rebuilds (dependency tracking)
    - Immediately runs the updated executable
"""

import os
import sys
import time
import subprocess
import argparse
import signal
from pathlib import Path
from typing import Set, Optional

try:
    from watchdog.observers import Observer
    from watchdog.events import FileSystemEventHandler
except ImportError:
    print("ERROR: watchdog library not installed")
    print("Install with: pip install watchdog")
    sys.exit(1)

class Colors:
    """ANSI color codes for professional terminal output."""
    RESET = '\033[0m'
    BOLD = '\033[1m'
    DIM = '\033[2m'
    
    # Status colors
    SUCCESS = '\033[32m'    # Green
    ERROR = '\033[31m'      # Red  
    WARNING = '\033[33m'    # Yellow
    INFO = '\033[36m'       # Cyan
    
    # Semantic colors
    ACCENT = '\033[35m'     # Magenta
    MUTED = '\033[90m'      # Gray

class BuildStats:
    """Track build statistics."""
    def __init__(self):
        self.total_builds = 0
        self.successful_builds = 0
        self.failed_builds = 0
        self.total_build_time = 0.0
        self.fastest_build = float('inf')
        self.slowest_build = 0.0

    def record_build(self, success: bool, build_time: float):
        self.total_builds += 1
        if success:
            self.successful_builds += 1
            self.total_build_time += build_time
            self.fastest_build = min(self.fastest_build, build_time)
            self.slowest_build = max(self.slowest_build, build_time)
        else:
            self.failed_builds += 1

    def print_stats(self):
        print(f"\n{Colors.INFO}Build Statistics:{Colors.RESET}")
        print(f"  Total builds: {self.total_builds}")
        print(f"  Successful: {Colors.SUCCESS}{self.successful_builds}{Colors.RESET}")
        print(f"  Failed: {Colors.ERROR}{self.failed_builds}{Colors.RESET}")
        if self.successful_builds > 0:
            avg_time = self.total_build_time / self.successful_builds
            print(f"  Average build time: {avg_time:.2f}s")
            print(f"  Fastest: {self.fastest_build:.2f}s")
            print(f"  Slowest: {self.slowest_build:.2f}s")

class HotReloadHandler(FileSystemEventHandler):
    """Handles file system events and triggers rebuilds."""
    
    def __init__(self, build_dir: str, executable: str, watch_extensions: Set[str], verbose: bool = False):
        self.build_dir = Path(build_dir)
        self.executable = executable
        self.watch_extensions = watch_extensions
        self.verbose = verbose
        self.last_build_time = 0
        self.build_cooldown = 1.0  # Prevent rapid consecutive builds
        self.stats = BuildStats()
        
        # Print initialization info
        self._print_header()

    def _print_header(self):
        """Print the startup header."""
        print(f"{Colors.BOLD}C++ Ninja Hot Reload System{Colors.RESET}")
        print("=" * 50)
        print(f"Build directory: {Colors.INFO}{self.build_dir}{Colors.RESET}")
        print(f"Executable: {Colors.INFO}{self.executable}{Colors.RESET}")
        print(f"Watching: {Colors.WARNING}{', '.join(sorted(self.watch_extensions))}{Colors.RESET}")
        print(f"Ready for changes... (Press Ctrl+C to stop)")
        print("=" * 50)

    def on_modified(self, event):
        """Called when a file is modified."""
        if event.is_directory:
            return
            
        file_path = Path(event.src_path)
        
        # Only watch relevant file types
        if file_path.suffix not in self.watch_extensions:
            return
            
        # Skip temporary files and build artifacts
        if any(skip in file_path.name for skip in ['.tmp', '.swp', '.o', '.a', '.so']):
            return
            
        # Prevent rapid consecutive builds
        current_time = time.time()
        if current_time - self.last_build_time < self.build_cooldown:
            if self.verbose:
                print(f"Skipping rapid rebuild (cooldown: {self.build_cooldown}s)")
            return
            
        self.last_build_time = current_time
        
        print(f"\n{Colors.WARNING}File changed: {Colors.BOLD}{file_path.name}{Colors.RESET}")
        self.trigger_rebuild()

    def trigger_rebuild(self):
        """Trigger Ninja rebuild and run the executable."""
        try:
            # Step 1: Run Ninja to rebuild
            print(f"{Colors.INFO}Running ninja...{Colors.RESET}")
            start_time = time.time()
            
            ninja_result = subprocess.run(
                ["ninja", "-C", str(self.build_dir)],
                capture_output=True,
                text=True
            )
            
            build_time = time.time() - start_time
            
            if ninja_result.returncode == 0:
                # Build succeeded
                self._handle_successful_build(ninja_result, build_time)
                self._run_executable()
            else:
                # Build failed
                self._handle_failed_build(ninja_result, build_time)
                
        except FileNotFoundError:
            print(f"{Colors.ERROR}ERROR: 'ninja' command not found{Colors.RESET}")
            print("   Install ninja: apt install ninja-build (Linux) or brew install ninja (Mac)")
        except Exception as e:
            print(f"{Colors.ERROR}Unexpected error: {e}{Colors.RESET}")

    def _handle_successful_build(self, result, build_time: float):
        """Handle successful build output."""
        self.stats.record_build(True, build_time)
        
        print(f"{Colors.SUCCESS}BUILD SUCCESSFUL ({build_time:.2f}s){Colors.RESET}")
        
        # Show what Ninja actually rebuilt
        if result.stdout.strip():
            build_steps = result.stdout.strip().split('\n')
            print(f"{Colors.INFO}Build steps:{Colors.RESET}")
            for line in build_steps:
                if line.startswith('['):
                    # Extract the action from ninja output like "[1/3] Building CXX object..."
                    if 'Building' in line:
                        print(f"  COMPILE: {Colors.MUTED}{line}{Colors.RESET}")
                    elif 'Linking' in line:
                        print(f"  LINK: {Colors.MUTED}{line}{Colors.RESET}")
                    else:
                        print(f"  {Colors.MUTED}{line}{Colors.RESET}")
        else:
            print(f"{Colors.SUCCESS}  No changes needed (up to date){Colors.RESET}")

    def _handle_failed_build(self, result, build_time: float):
        """Handle failed build output."""
        self.stats.record_build(False, build_time)
        
        print(f"{Colors.ERROR}BUILD FAILED ({build_time:.2f}s){Colors.RESET}")
        print(f"{Colors.ERROR}Compilation errors:{Colors.RESET}")
        
        # Show compilation errors in a readable format
        if result.stderr:
            error_lines = result.stderr.strip().split('\n')
            for line in error_lines:
                if line.strip():
                    print(f"  {Colors.ERROR}{line}{Colors.RESET}")
        
        if result.stdout:
            output_lines = result.stdout.strip().split('\n')
            for line in output_lines:
                if 'FAILED' in line or 'error:' in line.lower():
                    print(f"  {Colors.ERROR}{line}{Colors.RESET}")

    def _run_executable(self):
        """Run the built executable."""
        executable_path = self.build_dir / "bin" / self.executable
        
        # Try different common locations for the executable
        if not executable_path.exists():
            executable_path = self.build_dir / self.executable
        if not executable_path.exists():
            executable_path = self.build_dir / f"{self.executable}.exe"  # Windows
            
        if not executable_path.exists():
            print(f"{Colors.WARNING}Executable not found: {executable_path}{Colors.RESET}")
            print(f"  Looked in: {self.build_dir / 'bin'}, {self.build_dir}")
            return
            
        try:
            print(f"{Colors.ACCENT}Running {self.executable}...{Colors.RESET}")
            print(f"{Colors.MUTED}{'=' * 40}{Colors.RESET}")
            
            result = subprocess.run(
                [str(executable_path)],
                capture_output=True,
                text=True,
                timeout=30  # Prevent hanging
            )
            
            # Print program output
            if result.stdout:
                print(result.stdout.rstrip())
            if result.stderr:
                print(f"{Colors.WARNING}stderr: {result.stderr.rstrip()}{Colors.RESET}")
                
            print(f"{Colors.MUTED}{'=' * 40}{Colors.RESET}")
            
            if result.returncode != 0:
                print(f"{Colors.WARNING}Program exited with code {result.returncode}{Colors.RESET}")
                
        except subprocess.TimeoutExpired:
            print(f"{Colors.WARNING}Program timed out (>30s){Colors.RESET}")
        except Exception as e:
            print(f"{Colors.ERROR}Error running executable: {e}{Colors.RESET}")

def verify_build_system(build_dir: str) -> bool:
    """Verify that the build directory has Ninja files."""
    build_path = Path(build_dir)
    
    if not build_path.exists():
        print(f"{Colors.ERROR}Build directory '{build_dir}' does not exist{Colors.RESET}")
        print(f"  Run: {Colors.INFO}cmake -B {build_dir} -G Ninja{Colors.RESET}")
        return False
        
    ninja_file = build_path / "build.ninja"
    if not ninja_file.exists():
        print(f"{Colors.ERROR}No build.ninja found in '{build_dir}'{Colors.RESET}")
        print(f"  Run: {Colors.INFO}cmake -B {build_dir} -G Ninja{Colors.RESET}")
        return False
        
    print(f"{Colors.SUCCESS}Found Ninja build system in '{build_dir}'{Colors.RESET}")
    return True

def setup_signal_handlers(handler):
    """Setup signal handlers for graceful shutdown."""
    def signal_handler(signum, frame):
        print(f"\n{Colors.WARNING}Shutting down hot reload...{Colors.RESET}")
        handler.stats.print_stats()
        sys.exit(0)
    
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description="Hot reload system for C++ development using Ninja",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python hot_reload.py                          # Use defaults
  python hot_reload.py --build-dir build --executable hello
  python hot_reload.py --watch-extensions .cpp .h .hpp .cc
  python hot_reload.py --verbose              # Show debug info
        """
    )
    parser.add_argument(
        "--build-dir", 
        default="build", 
        help="Build directory containing build.ninja (default: build)"
    )
    parser.add_argument(
        "--executable", 
        default="ab_modules", 
        help="Name of executable to run (default: ab_modules)"
    )
    parser.add_argument(
        "--source-dir",
        default=".",
        help="Source directory to watch (default: current directory)"
    )
    parser.add_argument(
        "--watch-extensions",
        nargs="+",
        default=[".cpp", ".h", ".hpp", ".c", ".cc", ".cxx"],
        help="File extensions to watch (default: .cpp .h .hpp .c .cc .cxx)"
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Show verbose output"
    )
    parser.add_argument(
        "--cooldown",
        type=float,
        default=1.0,
        help="Cooldown between builds in seconds (default: 1.0)"
    )
    
    args = parser.parse_args()
    
    # Verify build system exists
    if not verify_build_system(args.build_dir):
        sys.exit(1)
    
    # Create event handler
    watch_extensions = set(args.watch_extensions)
    handler = HotReloadHandler(
        build_dir=args.build_dir,
        executable=args.executable,
        watch_extensions=watch_extensions,
        verbose=args.verbose
    )
    handler.build_cooldown = args.cooldown
    
    # Setup signal handlers for graceful shutdown
    setup_signal_handlers(handler)
    
    # Set up file system observer
    observer = Observer()
    observer.schedule(handler, args.source_dir, recursive=True)
    
    try:
        observer.start()
        
        # Trigger initial build
        print(f"{Colors.INFO}Performing initial build...{Colors.RESET}")
        handler.trigger_rebuild()
        
        print(f"\n{Colors.SUCCESS}Watching {args.source_dir} for changes...{Colors.RESET}")
        
        # Keep the script running
        while True:
            time.sleep(1)
            
    except KeyboardInterrupt:
        print(f"\n{Colors.WARNING}Stopping hot reload...{Colors.RESET}")
        handler.stats.print_stats()
        
    finally:
        observer.stop()
        observer.join()

if __name__ == "__main__":
    main()