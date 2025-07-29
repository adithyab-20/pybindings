import pytest
from ab_py_calculator import Calculator
from ab_py_calculator.ab_calculator import InvalidArgument


class TestCalculator:
    def setup_method(self) -> None:
        """Set up test fixtures before each test method."""
        self.calc = Calculator()

    def test_addition(self) -> None:
        """Test basic addition."""
        result = self.calc.add(2, 3)
        assert result == 5

        result = self.calc.add(-1, 1)
        assert result == 0

        result = self.calc.add(10, 20)
        assert result == 30

    def test_subtraction(self) -> None:
        """Test basic subtraction."""
        result = self.calc.subtract(5, 3)
        assert result == 2

        result = self.calc.subtract(0, 5)
        assert result == -5

    def test_multiplication(self) -> None:
        """Test basic multiplication."""
        result = self.calc.multiply(3, 4)
        assert result == 12

        result = self.calc.multiply(-2, 3)
        assert result == -6

        result = self.calc.multiply(0, 100)
        assert result == 0

    def test_division(self) -> None:
        """Test basic division."""
        result = self.calc.divide(10, 2)
        assert result == 5

        result = self.calc.divide(8, 2)
        assert result == 4

    def test_division_by_zero(self) -> None:
        """Test division by zero handling."""
        with pytest.raises(InvalidArgument, match="Division by zero"):
            self.calc.divide(5, 0)
