
# Shapes Drawing Application


This application is a GUI-based tool developed using C++ and the Qt framework. It allows users to draw geometric shapes on a canvas by executing commands through a command console. The logs of the operations are displayed in a log window. Additionally, the application provides an option to save the logs into a .log file.


## Features

### 1. Graphical Interface
 - **Canvas**: A display area where geometric shapes (``line``, ``triangle``, and ``rectangle``) are drawn.
 - **Command Console**: An input field for entering commands that create and manipulate shapes.
 - **Log Window**: A section where feedback (success or failure of the command) is displayed to the user.
 - **Save Logs**: A button to save all log entries into a ``.log`` file.

### 2. Command Interface
The following commands are supported to create and manipulate shapes:
```bash
create_line -name {line_name} -coord_1 {x1, y1} -coord_2 {x2, y2}
```

```bash
create_rectangle -name {rectangle_name} -coord_1 {x1, y1} -coord_2 {x2, y2}
```

```bash
create_triangle -name {triangle_name} -coord_1 {x1, y1} -coord_2 {x2, y2} -coord_3 {x3, y3}
```

### 3. Saving Logs
- **Save Logs Button**: After executing commands, all log entries can be saved into a ``.log`` file by clicking the "Save Logs" button.


## Additional Features
- Error Handling: If a command is incorrect, an error message is logged in the log window.
- Save Logs to File: All command execution logs are saved into a ``.log`` file when the "Save Logs" button is clicked.

## Design Patterns
- **Factory Pattern**: The application utilizes the Factory design pattern to create instances of different shapes (Triangle, Rectangle, Line).
- **Singleton Pattern**: The application has only one instance, while providing a global access point to this instance.
- **OOP Principles**: The application is structured using object-oriented principles to ensure flexibility and maintainability.

## How to Build and Run
### Prerequisites
- Qt 6.x or higher installed.
- C++17 compiler.
- ``qmake`` or ``cmake``

### Clone
```bash
git clone https://github.com/davitmartirosyan/QT_Shapes.git
cd QT_Shapes
```
### Build
```bash
mkdir build
cd build
qmake ../Shapes.pro
```
### Run
```bash
./Shapes
```

## Conclusion
This application demonstrates how to draw basic geometric ``shapes`` on a canvas using ``command-line`` inputs. ``Logs`` are generated for each action, and a log-saving feature allows users to save logs for future reference.
