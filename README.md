ChattY
==============

Chat client and server implemented in C++ and Qt 5.

THIS SOFTWARE IS RELEASED AS FREE SOFTWARE. YOU HAVE THE RIGHT TO USE, SHARE OR MODIFY IT IN ANY WAY YOU WANT. IT IS RELEASED WITH ABSOLUTELY NO WARRANTY TO THE EXENT OF APPLICABLE LAW.

System Requirements
==============

Tested with: 

* Mac OS X 10.7 and later
* Windows 7 and later
* Ubuntu 12.04 and later

Pre built binaries can be found at http://hfelo.se

Compiling
==============

- ChattY is written in C++11 and requires a compiler with support for it, for example g++ version 4.7 or later.

- ChattY requires a functional Qt 5 environment, which can be found here: http://qt-project.org/downloads

- On Mac OS X 10.9 Mavericks you need to install XCode Command Line Tools in order to clone and compile ChattY. You then need to install Qt 5 from http://qt-project.org/downloads

- On Ubuntu 13.10 and later you can install Qt 5 by using the following commands:

    sudo apt-get update
    
    sudo apt-get upgrade
    
    sudo apt-get install build-essential qt5-default git

Client
==

- To clone and compile the ChattY client on POSIX-compliant (Linux, OS X) systems:

    git clone https://github.com/hansfilipelo/ChattY.git
    
    cd ChattY/gui
    
    qmake Chatty_Mac.pro -config release
    
    make

- To clone and compile the ChattY client on Windows systems you need to install git from: http://git-scm.com/downloads. You then need to install Qt 5 from http://qt-project.org/downloads. After successfully installing these dependencies, open Git Shell and type:

    git clone https://github.com/hansfilipelo/ChattY.git

    Then open ChattY.pro using Qt Creator and compile for release.

Server
==

- To clone and compile the ChattY server on POSIX-compliant systems (Linux, OS X):

    git clone https://github.com/hansfilipelo/ChattY.git

    cd ChattY/server
    
    qmake ChattY_Win.pro -config release
    
    make
    
- To clone and compile the ChattY client on Windows systems you need to install git from: http://git-scm.com/downloads. You then need to install Qt 5 from http://qt-project.org/downloads. After successfully installing these dependencies open Git Shell and type:

    git clone https://github.com/hansfilipelo/ChattY.git

    Then open ChattYServer.pro using Qt Creator and compile for release.