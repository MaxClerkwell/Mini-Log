#pragma once

#include<string>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include<chrono>
#include<iostream>
#include<iomanip>

namespace fs = boost::filesystem;

namespace miniLog{

	
	enum miniMessage_T {status, warning, error};
	struct miniMessage{
		std::chrono::system_clock::time_point messageTime;
		message_T messageType;
		std::string message;

		miniMessage(message_T mType, const std::string & mString)
			:messageTime{std::chrono::system_clock::now()},
			messageType{mType},
			message{mString}
		{	
		}
	};

	std::string getTimeStr(const std::chrono::time_point<std::chrono::system_clock> & intime){
		std::time_t now{std::chrono::system_clock::to_time_t(intime)};
		std::string s(22, '\0');
		std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
		return s;
	}
	
	std::string getTimeStr(const miniMessage & m){
		return getTimeStr(m.messageTime);
	}


	template <typename T>
		T& operator<< (T& ofs, const miniMessage & m){
			ofs << getTimeStr(m);
			switch(m.messageType){
			case status:
				ofs << "STATUS:  ";
				break;
			case warning:
				ofs << "WARNING: ";
				break;
			case error:
				ofs << "ERROR:   ";
				break;
			}
			ofs << m.message;
			return ofs;
		}	

	struct miniLogger{
		fs::path p;

		miniLogger(const std::string & logpath, const std::string & Appname)
			:p{logpath}
		{
			fs::ofstream ofs{p, fs::ofstream::out|fs::ofstream::app};
			ofs     << std::endl
				<< "-------------------------------------------------" << std::endl
				<< "++++++++++++ Welcome to the Mini-Log ++++++++++++" << std::endl
				<< "++            Mini-Log was build by            ++" << std::endl
				<< "++              Stephan Bökelmann              ++" << std::endl
				<< "++             github: bjoekeldude             ++" << std::endl
				<< "++           2018 - Ruhr-Uni-Bochum            ++" << std::endl
				<< "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl
				<< getTimeStr(std::chrono::system_clock::now()) 
				<< "Start of logging " << Appname << std::endl;
			
		}

		void log(miniMessage & message){
			fs::ofstream ofs{p,fs::ofstream::out|fs::ofstream::app};
			ofs << message << std::endl;
		}
	};
}


