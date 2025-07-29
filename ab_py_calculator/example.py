#!/usr/bin/env python3
"""
Example usage of AB Python Calculator

This demonstrates the Python-C++ bindings in action.
"""

from ab_py_calculator import Calculator


def main() -> None:
    print("AB Python Calculator Example")
    print("=" * 40)

    # Create calculator
    print("\n1. Basic Calculator Operations:")
    calc = Calculator()

    # Perform some calculations
    result1 = calc.add(10, 5)
    print(f"10 + 5 = {result1}")

    result2 = calc.multiply(7, 8)
    print(f"7 * 8 = {result2}")

    result3 = calc.subtract(20, 3)
    print(f"20 - 3 = {result3}")

    result4 = calc.divide(15, 3)
    print(f"15 / 3 = {result4}")

    # Test division by zero handling
    print("\n2. Error Handling:")
    try:
        calc.divide(10, 0)
    except Exception as e:
        print(f"Division by zero correctly raises exception: {type(e).__name__}")


if __name__ == "__main__":
    main()
