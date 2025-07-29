"""Type stubs for ab_calculator C++ extension."""


class InvalidArgument(Exception):
    """Exception raised for invalid arguments (e.g., division by zero)."""
    ...


class Calculator:
    """High-performance calculator with C++ backend."""

    def __init__(self) -> None:
        """Initialize calculator."""
        ...

    def add(self, lhs: int, rhs: int) -> int:
        """Add two integers."""
        ...

    def subtract(self, lhs: int, rhs: int) -> int:
        """Subtract second integer from first."""
        ...

    def multiply(self, lhs: int, rhs: int) -> int:
        """Multiply two integers."""
        ...

    def divide(self, lhs: int, rhs: int) -> int:
        """Divide first integer by second (throws on division by zero)."""
        ...
