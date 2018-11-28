# Mini-Log
Mini-Log is a minimum structual-logging library. Header-Only and simple to use. 

## How to use Mini-Log
1) Clone Mini-Log into your project-folder
2) include miniLog.hpp
3) include <string>
4) set a 'const std::string log_path {"./my/relative/path/to/log.txt"};'
5) build a 'miniLog::debugLogger myLogger{log_path, "Application Name"};'

There is your Logger.

## Log a Message
Mini-Log has a debugMessage Type. If you want to log a message just use 
> miniLog::debugMessage myMessage{miniLog::message_T::status, std::string{"my status message"}

If you finally want to write your message apply it with myLogger.log(myMessage);
Mini-Log also features miniLog::message_T::error and miniLog::message_T::warning.

Mini-Log will append all messages in that file. To clear it, simply rm your logfile.txt. 
