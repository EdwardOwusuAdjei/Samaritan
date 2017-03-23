#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <string>

class database
{
public:
    database();
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    int save();
};

#endif // DATABASE_H
