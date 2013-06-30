/*!
    Multiverse Engine Project 5/5/2011 Core Panic.cpp

    This file contains Error Handler functions.
    
    Copyright (C) 2013 Multiverse Engine Project

    This program is free software;
    you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; 
    either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program; 
    if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
      
    Official source repository and project information can be found at
    https://github.com/codebase7/mengine
*/

#include "Panic.h"

std::string Panic::ERROR::ReturnLastError() const
{
        return this->LastError;
}

std::string Panic::ERROR::PanicHandler(std::string message, int moduleID, int log_level, bool killengine)
{
        // Init vars.
        fstream old_log_file;
        std::string temp_path = "";
        size_t size = 0;

        // Make sure the error message is not blank.
        if (message.size() <= 0)
        {
                // No message put generic responce.
                this->LastError = "PanicHandler : No error message specified";

                // Print error to stdout
                cout << "PanicHandler : No error message specified" <<"\n\n";

                // Check and see if we need to die.
                if (killengine == true)
                {
                        // Exit program.
                        exit(-1);
                }

                // Nope we don't so keep going!
                return "OK";
        }
        else
        {
                // Append the Module Name to the error message.
                switch(moduleID)
                {
                        case CORE_ID:
                            LastError = "CORE: ";
                            break;
                        case COMMON_ID:
                            LastError = "COMMON: ";
                            break;
                        case GAME_ID:
                            LastError = "GAME_MODULE: ";
                            break;
                        case OPENGL_ID:
                            LastError = "OPENGL_MODULE: ";
                            break;
                        case PORT_AUDIO_ID:
                            LastError = "Port Audio Subsystem: ";
                            break;
                        case ERROR_ID:
                            LastError = "Panic_Handler: ";
                            break;
                        default:
                            LastError = "UNKNOWN: ";
                            break;
                };

                // Set the message into the lasterror string.
                this->LastError += message;

                // Print error to stdout.
                cout << "\nPanicHandler: " << this->LastError <<"\n\n";
        }

        // Check and see if logging is enabled.
        if (this->logfile_enabled == true)
        {
                // Check and see if log level requires a log entry.
                if (log_level <= this->logLevel)
                {
                        // Check and see if the file is open.
                        if (this->logfile.is_open())
                        {
                                // Flush current buffer.
                                this->logfile.flush();

                                // If log entry count is above maximium,
                                if (this->currentLogLine >= this->maxLogLines)
                                {
                                        // Reset the log line count and reset file position.
                                        this->currentLogLine = 0;
                                        this->logfile.seekp(0, ios::beg);
                                        this->logfile.seekg(0, ios::beg);

                                        // Create old file name.
                                        temp_path = this->pathToLogFile;
                                        temp_path += ".old";

                                        // Try to open the file.
                                        old_log_file.open(temp_path.c_str(), ios::in | ios::out | ios::trunc);
                                        if (old_log_file.is_open())
                                        {
                                                    // Compute the size of the old log file.
                                                    this->logfile.seekg(0, ios::end);
                                                    size = this->logfile.tellg();
                                                    this->logfile.seekg(0, ios::beg);

                                                    // Copy the old log file.
                                                    for(size_t x = 0; x < size; x++)
                                                    {
                                                            old_log_file.put(this->logfile.get());
                                                    }

                                                    // Flush the old log.
                                                    old_log_file.flush();

                                                    // Close the old file.
                                                    old_log_file.close();
                                        }

                                        // Close the log_file and attempt to reopen it.
                                        this->logfile.close();
                                        this->logfile.open(this->pathToLogFile.c_str(), ios::in | ios::out | ios::trunc);
                                        if(!this->logfile.is_open())
                                        {
                                                // Could not open log file, disable logging.
                                                this->disable_logging();
                                                this->PanicHandler("Logging Disabled due to failed filestream");

                                                // Check and see if we need to die.
                                                if (killengine == true)
                                                {
                                                        exit(-1);
                                                }

                                                // We don't so return error.
                                                return "ERROR_LOG_DISABLED";
                                        }
                                }

                                // Write the log entry.
                                this->logfile << this->LastError << '\n';

                                // Flush the output buffer.
                                this->logfile.flush();

                                // Update the log entry count
                                this->currentLogLine++;
                        }
                }
        }

        // Check and see if we need to die.
        if (killengine == true)
        {
                // Exit program.
                exit(-1);
        }

        // Nope we don't so keep going!
        return "OK";
}

short Panic::ERROR::enable_logging(std::string path_to_logfile, short log_level, int max_lines)
{
        // Dumb check.
        if (path_to_logfile.size() <= 0)
        {
                // No valid path.
                return -5;
        }
        if (log_level <= 0)
        {
                // Invalid log level.
                return -5;
        }
        if (max_lines <= 0)
        {
                // Invalid max_lines.
                return -5;
        }
        if ((this->logfile_enabled) && (this->logfile.is_open()))
        {
                // Already logging data to disk.
                return -1;
        }

        // Attempt to open the file.
        this->logfile.open(path_to_logfile.c_str(), ios::in | ios::out | ios::trunc);
        if (this->logfile.is_open() == false)
        {
                // Could not open log file.
                return -9;
        }

        // Set the max log lines.
        this->maxLogLines = max_lines;

        // Set the log level.
        this->logLevel = log_level;

        // Set the path.
        this->pathToLogFile = path_to_logfile;

        // Flush the file.
        this->logfile.flush();

        // Set logfile_enabled to true.
        this->logfile_enabled = true;

        // Exit function.
        return 0;
}

void Panic::ERROR::disable_logging()
{
        // Check and see if the file handler is open.
        if ((this->logfile.is_open() == false) && (this->logfile_enabled == false))
        {
                // Nothing to do.
                return;
        }

        if (logfile.is_open() == true)
        {
                // Flush log file.
                this->logfile.flush();

                // Close it.
                this->logfile.close();
        }

        // Reset the vars.
        this->currentLogLine = 0;
        this->logLevel = 0;
        this->maxLogLines = 0;
        this->pathToLogFile = "";
        this->logfile_enabled = false;

        // Exit Function.
        return;
}

void Panic::FileStream_Status(Panic::ERROR & error, fstream & stream, int log_level)
{
        // Output status header.
        error.PanicHandler("FileStream_Status:", ERROR_ID, log_level);

        // Check if file stream is open.
        if (!(stream.is_open()))
        {
                // File stream is closed.
                error.PanicHandler("FileStream is closed", ERROR_ID, log_level);
        }
        else
        {
                // File stream is open.
                error.PanicHandler("FileStream is open", ERROR_ID, log_level);

                // Check the current file stream status.
                if (!(stream.good()))
                {
                        // Check and see why it is bad.
                        if (stream.eof())
                        {
                                // File stream is at eof.
                                error.PanicHandler("FileStream is at End of File, (EOF)", ERROR_ID, log_level);
                        }
                        else
                        {
                                // File stream error.
                                error.PanicHandler("FileStream is bad", ERROR_ID, log_level);
                        }
                }
                else
                {
                        // File stream is good.
                        error.PanicHandler("FileStream is good, no error", ERROR_ID, log_level);
                }
        }

        // Output end of filestream status.
        error.PanicHandler("End of FileStream_Status", ERROR_ID, log_level);

        // Exit function.
        return;
}

const char * Panic::Get_Library_Version()
{
        return PANIC_HANDLER_VERSION;
}

const char * Panic::Get_Library_Compile_Date()
{
        return PANIC_HANDLER_COMPILEDATE;
}

const char * Panic::Get_Library_Compile_Time()
{
        return PANIC_HANDLER_COMPILETIME;
}