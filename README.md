# Restaurant Order Management System

This project is a simple restaurant order management system that uses the `ncurses` library to provide a text-based user interface (TUI). The system allows you to add, cancel, search, and display orders.

## Features

- **Add Orders**: Add new orders with details such as order number, client name, date, status, and total amount.
- **Search Orders**: Search for orders by their order number.
- **Cancel Orders**: Cancel orders by changing their status to "cancelled".
- **Display Order History**: Display a list of all orders.
- **Display Pending Orders**: Display a list of orders that are in the "pending" status.

## Requirements

- `gcc` (GNU Compiler Collection)
- `ncurses` library

## Installation

### Linux

1. Install the `ncurses` library (if not already installed):
    ```sh
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```

2. Clone the repository:
    ```sh
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```

3. Compile the program:
    ```sh
    gcc -o order_management main.c -lncurses
    ```

### Windows

1. Install [Cygwin](https://www.cygwin.com/) or [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) with `gcc` and `ncurses` support.

2. Clone the repository:
    ```sh
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```

3. Compile the program using Cygwin or WSL:
    ```sh
    gcc -o order_management main.c -lncurses
    ```

### macOS

1. Install the `ncurses` library (if not already installed):
    ```sh
    brew install ncurses
    ```

2. Clone the repository:
    ```sh
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```

3. Compile the program:
    ```sh
    gcc -o order_management main.c -lncurses
    ```

## Usage

1. Run the compiled program:
    ```sh
    ./order_management
    ```

2. Follow the on-screen menu to add, search, cancel, and display orders.

## Example Commands

- **Add Order**: Follow the prompts to enter order details.
- **Search Order**: Enter the order number to search for a specific order.
- **Cancel Order**: Enter the order number to cancel it.
- **Display Order History**: View all orders.
- **Display Pending Orders**: View orders that are in the "pending" status.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- [ncurses](https://invisible-island.net/ncurses/) for providing the TUI library
- [GNU](https://www.gnu.org/software/gcc/) for the GCC compiler