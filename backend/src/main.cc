#include <server.hh>
#include <database.hh>
#include <memory>
#define INCLUDE_ATRC_STDLIB 1
#include <ATRC.hpp>
#include <fstream>

Database db;
std::string port = "9090";
bool verbose = false;

int main(int argc, char** argv) {
    try {
        std::cout << "Reading configuration file!" << std::endl;
        std::shared_ptr<ATRC_FD> fd = Read("backend.config", "utf-8", ".config");
        if(!fd) {
            std::cerr << "Failed to read configuration file!" << std::endl;
            return 1;
        }
        std::cout << "Configuration file read!" << std::endl;
        verbose = atrc_to_bool(ReadKey(fd, "CONFIG", "VERBOSE"));

        port = ReadKey(fd, "CONFIG", "PORT");
        if(verbose) std::cout << "Port: " << port << std::endl;
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << ReadKey(fd, "CONFIG", "WELCOME_MESSAGE") << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        
        if(verbose) std::cout << "Database: " << ReadKey(fd, "CONFIG", "DB_NAME") << std::endl;
        db = Database(ReadKey(fd, "CONFIG", "DB_NAME"));

        if(atrc_to_bool(ReadKey(fd, "CONFIG", "RESET_DB_ON_START"))){
            if(verbose)std::cout << "Deleting database!" << std::endl;
            std::fstream file(ReadKey(fd, "CONFIG", "DB_NAME"), std::ios::in);
            if(file.good()) {
                file.close();
                std::remove(ReadKey(fd, "CONFIG", "DB_NAME").c_str());
            }
        }

        if(verbose)std::cout << "Opening database!" << std::endl;
        if(!db.open(ReadKey(fd, "CONFIG", "DB_NAME"))) {
            if(atrc_to_bool(ReadKey(fd, "CONFIG", "CREATE_DB_ON_START"))){
                std::cerr << "Failed to open database, trying to create it!" << std::endl;
                if(!db.create_database(ReadKey(fd, "CONFIG", "DB_NAME"))) {
                    std::cerr << "Failed to create database!" << std::endl;
                    return 1;
                }
            }
        }
        if(verbose)std::cout << "Database opened!" << std::endl;
        
        if(atrc_to_bool(ReadKey(fd, "CONFIG", "CREATE_TABLES_ON_START"))){
            if(verbose)std::cout << "Creating tables!" << std::endl;
            db.create_tables();
            if(verbose)std::cout << "Tables created!" << std::endl;
        }

        if(atrc_to_bool(ReadKey(fd, "CONFIG", "INSERT_SAMPLE_DATA_ON_START"))){        
            if(verbose)std::cout << "Inserting sample data!" << std::endl;
            db.insert_sample_data();
            if(verbose)std::cout << "Sample data inserted!" << std::endl;
        }


        std::cout << "Starting server!" << std::endl;
        Server server((short)atrc_to_uint64_t(ReadKey(fd, "CONFIG", "PORT")));
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    db.close();
    return 0;
}
