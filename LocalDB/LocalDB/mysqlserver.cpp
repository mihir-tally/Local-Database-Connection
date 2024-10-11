#include "common.hpp"

eGoodBad TMySqlServer::MySqlDataBase (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                        eBool pCreateDb, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);
        return BAD;
    }

    try {

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        bool db_exists = res->next ();

        if (pCreateDb) {

            if (db_exists) {

                HandleBadReponse (DATABASE_ALREADY_EXIST, pBadResponse);
                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("CREATE DATABASE " + string (pDataBaseName) + ";");
                con->setSchema (pDataBaseName);
            }
        } else {
            
            if (!db_exists) {

                HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("DROP DATABASE " + string (pDataBaseName)+ ";");
            }
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return BAD;
    }

    return GOOD;
}

eGoodBad TMySqlServer::MySqlCreateLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                              AStrPtr pColumnNameAndDataType, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        // Now proceed to create the table
        stmt = con->createStatement ();

        // Check if the table already exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (res->next()) {

            // Table already exists
            HandleBadReponse (TABLE_ALREADY_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        stmt->execute ("CREATE TABLE " + string (pTableName) + " (" + string (pColumnNameAndDataType) + ");");

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlDeleteLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        res   = nullptr;
        pstmt = nullptr;
        stmt  = nullptr;

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");

        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);

        res = pstmt->executeQuery ();

        if (res->next ()) {

            stmt->execute ("DROP TABLE " + string(pTableName));

        }
        else {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlAlterLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                             AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        Driver *              driver      = nullptr;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        string                query;

    try {
        // Initialize the driver and connect to the database
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        res   = nullptr;
        pstmt = nullptr;

        con->setSchema (pDataBaseName);

        // Check if the table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        res   = nullptr;
        pstmt = nullptr;

        // Check if the column already exists
        pstmt = con->prepareStatement ("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pColumnName);
        res = pstmt->executeQuery ();

        if (res->next()) {

            HandleBadReponse (COLUMN_ALREADY_EXIST, pBadResponse);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        res   = nullptr;
        pstmt = nullptr;

        // Alter the table to add the new column
        stmt  = con->createStatement ();
        query = "ALTER TABLE " + string (pTableName) + " ADD COLUMN " + string (pColumnName) + " " + string (pColumnDataType) + ";";
        stmt->execute (query);

        delete stmt;
        delete con;
        return GOOD;

    }
    catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        if (res) delete res;
        if (pstmt) delete pstmt;
        if (stmt) delete stmt;
        if (con) delete con;

        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlInsertDataIntoTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr * pTableNameArray,
                                                 AStrPtr * pColumnNamesArray, AStrPtr * pValuesArray, ULong pArraySize, StrPtr& pBadResponse)
{
        Driver *              driver      = nullptr;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        string                query;

    // Check if ArraySize is 0
    if (pArraySize == 0) {

        HandleBadReponse (EMPTY_DATA, pBadResponse);
        return BAD;    
    }
    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);
        con->setAutoCommit (false); // Set auto-commit to false

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Database does not exist
            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            con->setAutoCommit (true); // Enable auto-commit after commit

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);

        for (ULong i = 0; i < pArraySize; i++) {

            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableNameArray[i]);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                // Table does not exist
                HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

                con->rollback (); // Rollback the transaction in case of an error
                con->setAutoCommit (true); // Enable auto-commit after commit

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;

            stmt = con->createStatement ();

            // Construct the SQL query to insert data into the table
            query = "INSERT INTO " + string (pTableNameArray[i]) + " " + string (pColumnNamesArray[i]) + " VALUES " + string (pValuesArray[i]) + ";";

            // Execute the query
            stmt->execute (query);

            delete stmt;
        }
        con->commit (); // Commit the transaction
        con->setAutoCommit (true); // Enable auto-commit after commit
        delete con;
        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        if (con != nullptr) {

            con->rollback (); // Rollback the transaction in case of an error
            con->setAutoCommit (true); // Enable auto-commit after commit
        }

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlDeleteDataFromTable (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition,
                                                 StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        
        res   = nullptr;
        pstmt = nullptr;

        // Delete all data from the table
        stmt = con->createStatement ();

        if (pArgc == 7) {

            query = "DELETE FROM " + string (pTableName) + " WHERE " + string (pCondition) + ";";

        } else {

            query = "DELETE FROM " + string (pTableName) + ";";
        }


        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlUpdateColumnData (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                              AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse)
{
        Driver *               driver    = nullptr;
        Connection *           con       = nullptr;
        Statement *            stmt      = nullptr;
        PreparedStatement *    pstmt     = nullptr;
        ResultSet *            res       = nullptr;
        string                 query;
        CAStrPtr               bad_resp  = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            // Table does not exist
            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Delete all data from the table
        stmt  = con->createStatement ();
        query = "UPDATE " + string (pTableName) + " SET " + string (pColumnDataValue) + " WHERE " + string (pConditionData) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlAddForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                           AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    }
    catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        return BAD;
    }

    try {
        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res = nullptr;
        pstmt = nullptr;

        // Check if the main table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;


        // Check if the reference table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pReferenceTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (REFERENCE_TABLE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Execute the ALTER TABLE query to add foreign key constraint
        stmt = con->createStatement ();
        string query = "ALTER TABLE " + string (pTableName) + " ADD CONSTRAINT " + string (pForeignKeyName) + " FOREIGN KEY (" + string (pColumnName) + ") REFERENCES " + string (pReferenceTableName) + "(" + string (pColumnName) + ") ON DELETE CASCADE ON UPDATE CASCADE;";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    }
    catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlDropForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                            AStrPtr pForeignKeyName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);
        return BAD;
    }

    try {
        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res  = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the foreign key constraint exists
        pstmt = con->prepareStatement ("SELECT CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND CONSTRAINT_NAME = ? AND CONSTRAINT_TYPE = 'FOREIGN KEY'");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pForeignKeyName);
        res  = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (FOREIGN_KEY_CONSTRAINT_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Execute the ALTER TABLE query to drop the foreign key constraint
        stmt  = con->createStatement ();
        query = "ALTER TABLE " + string (pTableName) + " DROP FOREIGN KEY " + string (pForeignKeyName) + ";";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    }
    catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;

        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlCreateTrigger (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName,
                                           AStrPtr pTableName, AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        Statement *            stmt        = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {


        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {
        // Check if database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if trigger exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TRIGGER_NAME FROM INFORMATION_SCHEMA.TRIGGERS WHERE TRIGGER_SCHEMA = ? AND TRIGGER_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTriggerName);
        res  = pstmt->executeQuery ();

        if (res->next ()) {
            // Trigger already exists
            HandleBadReponse (TRIGGER_ALREADY_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Create trigger query
        stmt = con->createStatement ();

        if (pArgc == 9) {

            query = "CREATE TRIGGER " + string (pTriggerName) + " " + string (pActivationTime) + " " +string (pTriggerEvent) + " ON " +string (pTableName) +" FOR EACH ROW " + " SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '" + 
                     string (pTableName) + " does not support creation/deletion/updation of data';";

        } else {

            query = "CREATE TRIGGER " + string (pTriggerName) + " " + string (pActivationTime) + " " + string (pTriggerEvent) + " ON " + string (pTableName) + " FOR EACH ROW " + string (pTriggerCondition) + ";";
        }

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlDropTrigger (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        HandleBadReponse (e.what (), pBadResponse);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res  = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the trigger exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TRIGGER_NAME FROM INFORMATION_SCHEMA.TRIGGERS WHERE TRIGGER_SCHEMA = ? AND TRIGGER_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTriggerName);
        res  = pstmt->executeQuery ();

        if (!res->next()) {
            // Trigger does not exist
            HandleBadReponse (TRIGGER_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Drop the trigger
        stmt  = con->createStatement ();
        query = "DROP TRIGGER " + string (pTriggerName) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MyShowTableColumnData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                              AStrPtr pColumnName, AStrPtr& pResultString, StrPtr& pBadResponse)
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData *    meta_data         = nullptr;
        string                 query;
        ULong                  result_string_len;
        int                    column_count;
        eBool                  is_general_log    = FALSE;

    try {

        driver = get_driver_instance ();
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what(), pBadResponse);

        return BAD;
    }

    try {

        if (strcmp (pTableName, "mysql.general_log") == 0) {

            is_general_log = TRUE;
        }

        if (!is_general_log) {

            pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;

            con->setSchema (pDataBaseName);
            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableName);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;
        }

        stmt = con->createStatement ();

        if (is_general_log) {

            query = "SELECT * FROM " + string (pTableName);

        } else if (pArgc == 7) {

            query = "SELECT " + string (pColumnName) + " FROM " + string (pTableName);

        } else {

            query = "SELECT * FROM " + string (pTableName);
        }

        res          = stmt->executeQuery (query);
        meta_data    = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        rapidjson::Document json_document;
        json_document.SetObject ();

        // Array for columns
        rapidjson::Value columns_array (rapidjson::kArrayType);

        for (int i = 1; i <= column_count; ++i) {

            rapidjson::Value column_object (rapidjson::kObjectType);
            rapidjson::Value column_name;
            rapidjson::Value column_type;

            column_name.SetString (meta_data->getColumnName (i).c_str (), json_document.GetAllocator ());
            column_type.SetString (meta_data->getColumnTypeName (i).c_str (), json_document.GetAllocator ());

            column_object.AddMember ("Name", column_name, json_document.GetAllocator ());
            column_object.AddMember ("Type", column_type, json_document.GetAllocator ());

            columns_array.PushBack (column_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("ColumnsData", columns_array, json_document.GetAllocator ());

        // Array for rows
        rapidjson::Value data_array (rapidjson::kArrayType);

        while (res->next ()) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            if (column_count == 0) {

                break;
            }
            for (int j = 1; j <= column_count; ++j) {

                rapidjson::Value column_name;
                rapidjson::Value column_value;

                column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());

                row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
            }
            data_array.PushBack (row_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("RowsData", data_array, json_document.GetAllocator ());

        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
        json_document.Accept (writer);

        result_string_len = (strlen (buffer.GetString()));
        pResultString = (AStrPtr) malloc ((result_string_len + 1) * sizeof (AChar));
        strcpy (pResultString, buffer.GetString());

        delete stmt;
        delete con;
        delete res;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::MySqlShowForeignKeyData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                                AStrPtr pTableName, AStrPtr& pResultString, StrPtr& pBadResponse)
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData *    meta_data         = nullptr;
        AStrPtr                result_string;
        string                 query;
        ULong                  result_string_len;
        int                    column_count;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    }catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);
        return BAD;
    }

    try {
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        con->setSchema (pDataBaseName);

        if (pArgc == 6) {

            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableName);
            res  = pstmt->executeQuery ();

            if (!res->next ()) {

                HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);

                delete res;
                delete pstmt;
                delete con;

                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;
        }

        stmt = con->createStatement ();

        if (pArgc == 6) {

            query = "SELECT table_name, constraint_name, column_name, referenced_table_name, referenced_column_name FROM information_schema.key_column_usage WHERE table_schema = '" + string (pDataBaseName) + "' AND table_name = '" + string (pTableName) + "' AND referenced_table_name IS NOT NULL;";
        
        } else {

            query = "SELECT table_name, constraint_name, column_name, referenced_table_name, referenced_column_name FROM information_schema.key_column_usage WHERE table_schema = '" + string (pDataBaseName) + "' AND referenced_table_name IS NOT NULL;";
        }

        res          = stmt->executeQuery (query);
        meta_data    = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        rapidjson::Document json_document;
        json_document.SetObject ();

        rapidjson::Value data_array (rapidjson::kArrayType);

        while (res->next ()) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            for (int j = 1; j <= column_count; ++j) {

                rapidjson::Value column_name;
                rapidjson::Value column_value;

                column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());
                row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
            }
            data_array.PushBack (row_object, json_document.GetAllocator ());
        }

        json_document.AddMember ("ForeignKeyTable", data_array, json_document.GetAllocator ());

        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
        json_document.Accept (writer);

        result_string_len = (strlen (buffer.GetString ()));
        pResultString     = (AStrPtr) malloc((result_string_len + 1) * sizeof (AChar));
        strcpy (pResultString, buffer.GetString ());

        delete stmt;
        delete con;
        delete res;

        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;

        return BAD;
    }
}

eGoodBad TMySqlServer::PerformMysqlJoin (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition, AStrPtr pSetOrFromCondtion, AStrPtr * pTableNameArray,
                                         ULong pTableNameArraySize, AStrPtr * pOnConditionArray, ULong pOnConditionArraySize, AStrPtr pWhereCondition, AStrPtr pOrderByCondition, AStrPtr& pResultString, StrPtr& pBadResponse)
{
        Driver *               driver             = nullptr;
        Connection *           con                = nullptr;
        Statement *            stmt               = nullptr;
        PreparedStatement *    pstmt              = nullptr;
        ResultSet *            res                = nullptr;
        ResultSetMetaData *    meta_data          = nullptr;
        string                 query;
        bool                   is_select_query    = false;
        ULong                  result_string_len;
        int                    column_count;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);
        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Set the schema
        con->setSchema (pDataBaseName);

        stmt = con->createStatement ();

        switch (pJoinType) {

            case INNER_JOIN_TYPE:
            case LEFT_JOIN_TYPE:
            case RIGHT_JOIN_TYPE:
            case CROSS_JOIN_TYPE:
            case NATURAL_JOIN_TYPE:
            case EQUI_JOIN_TYPE:
                is_select_query = true;

                query = "SELECT " + string (pSelectCondition) + " FROM " + string (pSetOrFromCondtion);
                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    switch (pJoinType) {

                        case INNER_JOIN_TYPE:

                            query += " INNER JOIN " + string(pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case LEFT_JOIN_TYPE:

                            query += " LEFT JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case RIGHT_JOIN_TYPE:
                        
                            query += " RIGHT JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case CROSS_JOIN_TYPE:
                            
                            query += " CROSS JOIN " + string (pTableNameArray[i]);
                            break;

                        case NATURAL_JOIN_TYPE:
                             
                            query += " NATURAL JOIN " + string (pTableNameArray[i]);
                            break;

                        default:
                            break;
                    }
                }
                break;

            case DELETE_JOIN_TYPE:

                query = "DELETE " + string (pSelectCondition) + " FROM " + string (pSetOrFromCondtion);

                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    query += " JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                }
                break;

            case UPDATE_JOIN_TYPE:

                query = "UPDATE " + string (pSelectCondition);

                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    query += " JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                }
                query += " SET " + string (pSetOrFromCondtion);
                break;
        
            default:
             
                // Invalid Join type
                HandleBadReponse (TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE, pBadResponse);
                delete stmt;
                delete con;
                return BAD;
        }

        if (pWhereCondition && *pWhereCondition) {

            query += " WHERE " + string (pWhereCondition);
        }

        if (pOrderByCondition && *pOrderByCondition) {

            query += " ORDER BY " + string (pOrderByCondition);
        }
        query += ";";

        if (is_select_query) {

            res          = stmt->executeQuery (query);
            meta_data    = res->getMetaData ();
            column_count = meta_data->getColumnCount ();

            Document json_document;
            json_document.SetObject ();
            Document::AllocatorType& allocator = json_document.GetAllocator();

            rapidjson::Value data_array (rapidjson::kArrayType);
            int itr = 1;

            while (res->next ()) {

                string table_name = meta_data->getTableName(itr);
                Value row_object (kObjectType);
                Value row_object2 (kObjectType);

                Recursion (itr, column_count, table_name, meta_data, res, row_object, allocator);

                row_object2.AddMember (rapidjson::Value(table_name.c_str (), allocator), row_object, allocator);
                data_array.PushBack (row_object2, json_document.GetAllocator ());
            }
            json_document.AddMember ("Join Data", data_array, json_document.GetAllocator ());

            //// Convert JSON document to string
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
            json_document.Accept (writer);

            result_string_len = (strlen (buffer.GetString ()));
            pResultString     = (AStrPtr) malloc ((result_string_len + 1) * sizeof (AChar));
            strcpy (pResultString, buffer.GetString ());

            delete res;
            res = nullptr;

        } else {

            stmt->executeUpdate (query);
        }

        delete stmt;
        delete con;
        return GOOD;

    }
    catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TMySqlServer::CheckMySqlServerStatus (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, StrPtr& pBadResponse)
{
    Driver *        driver = nullptr;
    Connection *    con    = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

        if (con->isValid ()) {

            if (con->isClosed ()) {

                HandleBadReponse (MYSQL_SERVER_NOT_RESPONDING, pBadResponse);

                delete con;
                return BAD;
            }
            delete con;
            return GOOD;
        }
        else {

            HandleBadReponse (MYSQL_SERVER_FAILED_CONN, pBadResponse);

            delete con;
            return BAD;
        }

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete con;
        return BAD;
    }
}

void TMySqlServer::Recursion (int pItr, int pMainCount, string& pTableName, ResultSetMetaData* meta_data, ResultSet* res, Value& pRowObject, Document::AllocatorType& pAllocator)
{
    if (pItr == pMainCount || pTableName.empty()) {

        return;
    }
    string table_name;
    for (int i = pItr; i <= pMainCount; i++) {
        table_name = meta_data->getTableName(i);

        if (table_name == pTableName) {

            std::string column_name = meta_data->getColumnName(i);
            std::string column_value = res->getString(i);
            if (!column_value.empty()) {

                rapidjson::Value column_key;
                rapidjson::Value column_val;
                column_key.SetString(column_name.c_str(), pAllocator);
                column_val.SetString(column_value.c_str(), pAllocator);
                pRowObject.AddMember(column_key, column_val, pAllocator);
            }


        } else {
            Value row_object3 (kObjectType);
            Recursion (i, pMainCount, table_name, meta_data, res, row_object3, pAllocator);
            if (row_object3.IsObject() && row_object3.MemberCount() > 0) {
                pRowObject.AddMember(rapidjson::Value(table_name.c_str(), pAllocator), row_object3, pAllocator);
            }
            return;
            
        }
    }
}

eGoodBad TMySqlServer::MySqlSetGeneralLog (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction,
                                           StrPtr& pBadResponse) 
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {


        HandleBadReponse (e.what (), pBadResponse);
        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Set the schema
        con->setSchema (pDataBaseName);

        stmt = con->createStatement ();

        switch (pLogAction) {

            case ACTION_TYPE_ENABLE:

                // Enable general log and set log output to table
                stmt->execute ("SET global general_log = 1;");
                stmt->execute ("SET global log_output = 'table';");
                break;

            case ACTION_TYPE_DISABLE:

                stmt->execute ("SET global general_log = 0;");
                break;

            case ACTION_TYPE_DELETE:
                // Delete general log data
                stmt->execute ("truncate table mysql.general_log;");
                break;

            default:
                // Invalid action type
                HandleBadReponse (TDL_ERROR_INCORRECT_ACTION_TYPE, pBadResponse);
                delete stmt;
                delete con;
                return BAD;
        }

        delete stmt;
        delete con;
        return GOOD;

    } catch (SQLException& e) {

        HandleBadReponse (e.what (), pBadResponse);

        delete stmt;
        delete con;
        return BAD;
    }
}
