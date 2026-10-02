# BagTagPrinter

BagTagPrinter is a Windows desktop application built with **C++ and Qt** for quickly creating and printing bag tags in dry-cleaning and commercial environments.

The application was created to simplify the process of printing standardized bag identification tags using an **Epson thermal receipt printer**.

## Current Version

**v0.1.0**

This is the first working development version of BagTagPrinter.

## Features

- Simple desktop interface designed for quick employee use
- Bag type selection using dedicated buttons
- Employee initials input
- Automatic date and time generation
- Direct printing to supported thermal printers
- Epson thermal receipt printer support
- Custom bag-tag formatting
- Printer status display
- Custom application icon
- Built with Qt Widgets and C++

## Printer

BagTagPrinter is currently being developed and tested with an:

**Epson TM-T88V thermal receipt printer**

The application uses Qt's `QPrinter`, `QPrinterInfo`, and `QPainter` functionality to communicate with the Windows printing system and generate the bag tag.

## Built With

- C++17
- Qt 6
- Qt Widgets
- Qt Print Support
- CMake
- MinGW
- Qt Creator

## Project Structure

```text
BagTagPrinter/
├── CMakeLists.txt
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── resources.qrc
├── app.rc
├── Oceanside_Utility_Printer.ico
└── README.md
```

## Building the Project

### Requirements

To build BagTagPrinter, you will need:

- Qt 6
- Qt Creator or another compatible C++ IDE
- CMake
- A C++17-compatible compiler

### Build

Clone the repository:

```bash
git clone https://github.com/D2007jr/BagTagPrinter.git
```

Open the project in Qt Creator by opening:

```text
CMakeLists.txt
```

Configure a compatible Qt kit and build the application.

## Screenshots

Screenshots of the application will be added as development continues.

## Development Status

BagTagPrinter is currently under active development.

Current version:

v0.1.0

Future versions may include additional printer controls, improved user-interface features, configuration options, and other workflow improvements.

## Author

**Daniel Nieto**

GitHub: **D2007jr**

## License

This project is currently provided as an open-source project. A formal license may be added in a future release.
