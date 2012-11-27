SOLAS Match Worker Daemon
============================

## What is this?

This is the back end to the SOLAS Match web application. It is used
to process things asynchronously. It connects to the same MySQL DB 
as the main web application and communicates asynchronously using
RabbitMQ. This is an AMQP based message queueing architecture for
cross platform IPC. Once the worker daemon has been started it
connects to the RabbitMQ server mentioned in the conf file and starts
processing any messages found. It is massively parralelised with each
consumer running on a different thread. Once a message has been 
consumed a new thread is launched into a locally managed threadpool
to handle the message while the original thread goes back to polling
RabbitMQ.

## System Requirements

The SOLAS Match Worker Daemon was built using Qt 4.8 on Ubuntu 12.04
but it should work on a cross platform environment.

# Contact

Contact:

    Reinhard Schäler <reinhard.schaler@ul.ie>
  
Coded by:
    
    David O Carroll <david.ocarroll@ul.ie>

# Installation

A number of external libraries are required to run this daemon:

## Dependencies

The RabbitMQ C library can be found at:

    https://github.com/alanxz/rabbitmq-c

Follow the instruction in the README file to install.

A wrapper for the RabbitMQ C library can be found at:

    https://github.com/akalend/amqpcpp

The tested version is at commit b5d00628c80e3c4c0c8d6d0e8b272510138a42fd

Follow the instructions in the README to compile.

Once compiled move the library file (.a) to /usr/local/lib

Move the header files (found in ./include/) to /usr/local/include

Download the latest version of Qxt from: http://dev.libqxt.org/libqxt/downloads

Follow the README to install: http://dev.libqxt.org/libqxt/wiki/user_guide

To install ctemplate run:
* sudo apt-get install libctemplate-dev libctemplate0

To install protobufs:
* Run sudo apt-get install libprotobuf7 protobuf-compiler protobuf-c-compiler libprotobuf-dev

## Configuration File

* Edit ./conf.ini with your details.
* The database section specifies MySQL DB connection settings
* Enter your MySQL connection settings here.
* The messaging section contains RabbitMQ related connection settings
* Enter your RabbitMQ details here
* The site section is currently unused
* Copy ./conf.ini to /etc/SOLAS-Match/conf.ini

## Compiling and installing

* To edit the source code open the project file ./SOLASMatchWorkerDaemon.pro
in QtCreator.
* Run the project to compile and start it. 
