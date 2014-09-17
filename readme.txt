Z Launcher 1.0

Release Date: September 16, 2014
Development Time: 2 Days
Developer: Kevin Scroggins (nitro glycerine)
E-Mail: nitro404@gmail.com
Website: http://www.nitro404.com
Requirements: Microsoft Windows, DOSBox (0.72), Z (Installation & ISO)

==========
 FEATURES
==========
  + Simple text based interface.
  + Easy access to video / sound setup.
  + Full networking & multiplayer support through IPX tunnelling in DOSBox.
  + Verification of DOSBox, game and any other required files.
  + Custom designed, easy to edit file formats.
  + Custom pseudo-scripting system for generating dynamic DOSBox scripts.
  + Platform-independent code design using Qt's Core library.

=============
 DESCRIPTION
=============
  A simple, easy to use launcher for the Bitmap Brothers' classic 1995 MS-DOS
  strategy game, Z, complete with DOSBox integration.
  
  Features a basic text-based interface, multiplayer support, proram arguments
  for quick launching through shortcuts or scripts, easy to edit file formats
  and customizable DOSBox scripts.
  
  If you happen to have any complaints, suggestions, bugs or comments, please
  feel free to send them my way! If you wish to contact me using something
  other than e-mail, alternative contact options are available on my website.
  Thank you!

============
 HOW TO USE
============
  Simply place the contents of this archive into a folder containing an
  installation of Z, along with an ISO image of the game disc in the same
  folder. Then simply open the launcher and play away! If there are any error
  messages, such as missing files - they will be displayed before the program
  displays the main menu.

  A copy of DOSBox will also be required, default is set to a subdirectory
  named "DOSBox" within the current working directory. Tested with DOSBox 0.72,
  though other versions should work as well.
  
  If you wish to have the game and ISO located in a parent folder (or any other
  folder for that matter), you can customize the paths and such once the
  initial settings file (Z Launcher.ini) has been generated. Use . for working
  directory and .. for parent directory. Game directory and DOSBox directories
  can also be changed in the generated settings file.

===================
 PROGRAM ARGUMENTS
===================
  -f \"Settings.ini\" - Specifies an alternate settings file to use.
  -m DOSBox/Windows - Specifies launcher mode, default: DOSBox.
  -t Game/Setup Sound/Setup Video/Client/Server - Specifies game type, default: Game.
  -ip 127.0.0.1 - Specifies host IP address if running in client mode.
  -? - Displays a help message with argument information.

==================
 PROGRAM COMMANDS
==================
       z -------- Start Z in single player mode.
   [r]un -------- ""
    [g]o -------- ""
[l]aunch -------- ""
   start -------- ""
[c]lient -------- Start Z in multiplayer client mode.
[s]erver -------- ""
 [a]udio -------- Run sound setup.
   sound -------- ""
 [v]ideo -------- Run video setup.
 connect <args> - Obtains the IP address of the host server.
      ip <args> - ""
  [t]ype <args> - Change game type (Single / Multiplayer).
  [m]ode <args> - Change launcher mode (Regular / DOSBox).
  [b]ack -------- Returns to the previous menu (if applicable).
  [h]elp -------- Displays a help message with command information.
       ? -------- ""
  [q]uit -------- Closes the launcher.
  e[x]it -------- ""

NOTES:
  + [x]yz  - Means you can run this command by typing only "x" or the full "xyz".
             ie. h or help to display help.
  + <args> - The area where you specify the arguments to this command.
             Arguments are usually optional and a prompt will be run instead,
             if no arguments are specified.
             ie. ip 127.0.0.1 or m DOSBox

===========
 COMPILING
===========
  If you wish to re-compile the program using the provided source code, you are
  welcome to do so as long as you don't take credit for my hard work and keep
  it for personal use.

  The source files can be obtained from the public git repository at the
  following link: https://github.com/nitro404/z_launcher
  
  The source code was written using C++ with Microsoft Visual Studio 2013, and
  as such all Visual Studio project files are also provided. Other IDEs are not
  supported, but if you choose to try and make the project compile in a
  different IDE, this is your choice and I assume no responsibility, nor will I
  help you to get it set up in a different environment.

  You will also need to have Qt 5 installed (the project was compiled with Qt
  version 5.3.1), and you may need to update the project's include and library
  directories. An additional library, Visual Leak Detector is also used in
  debug mode, so you can remove the include in Main.cpp and the project's
  include / library entries if you want, as it is not mandatory. You can
  download these libraries at the following links:

  Qt: http://qt-project.org/downloads
  Visual Leak Detector: https://vld.codeplex.com/

==============
 SCRIPT FILES
==============
  The scripting language used has two basic features:

  1. Variable Substitution
     - Will substitute each variable with the corresponding value as passed in
       with the argument list. If the value does not exist, it will simply omit
       the original variable, leaving it empty.
     - Variables are specified with the ':' character on each side of a
       variable name.
     - Variable names are not case sensitive.
     - ie. :Z: would be replaced with "ZED.EXE"

  2. Conditionals
     - Will substitute each conditional with the specified text if the variable
       name specified in the conditional statement exists and has a non-empty
       value, otherwise the whole conditional statement is omitted and will be
       left empty.
     - Conditionals are specified inside of '<' and '>' characters with a '|'
       character separating the variable name and the conditional text.
     - Variable names are not case sensitive.
     - Conditional replacement text supports both nested variables and other
       conditional statements.
     - ie. <GAMEPATH|CD :GAMEPATH:> would be replaced with "CD Z" if the
       variable "GAMEPATH" exists and has a non-empty value of "Z".

===========
 CHANGELOG
===========
  Version 1.0 (September 16, 2014)
    + Initial release!
