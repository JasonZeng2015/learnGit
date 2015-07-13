#ifndef _DB_MYSQL_H_
#define _DB_MYSQL_H_

#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>
#include <exception>
using namespace std;

class MysqlRecordset
{
	public:
		const string& GetItem(unsigned int nRow, unsigned int nCol) const
		{
			//return rows[nRow][nCol];
			return rows.at(nRow).at(nCol);
		}

		const string& GetItem(unsigned int nRow, const string& name) const
		{
			int index = GetFieldIndex(name);
			//return rows[nRow][index];
			return rows.at(nRow).at(index);
		}

		int GetFieldIndex(const string &name) const; 
		unsigned int GetRows() const
		{
			return rows.size();
		}

		unsigned int GetCols() const
		{
			return fields.size();
		}

		typedef struct Field
		{
			string name;
			unsigned int index;
		} FIELD;

		void clear()
		{
			rows.clear();
			fields.clear();
		}
		typedef vector<FIELD> FIELDS;
		typedef vector<string> ROW;

	public:
		vector<ROW> rows;
		FIELDS fields;
};
class DB_MYSQL
{
	public:
		DB_MYSQL();
		~DB_MYSQL();
		void connect(const char* host, const char* user, const char* passwd, const char* db_name, unsigned int port);
		int prepare(const char* sql);
		int execSQL(const char* sql);
		MysqlRecordset query(const char* sql);
		int get_result();
		int commit();
		int rollback();
		void disconnect();
	private:
		MYSQL *mysql;
};

class DBException:public exception
{
	public:
	DBException(string s1){
		s = s1;
	}

	~DBException()throw(){
	}

	void p(){
		cout<<s<<endl;
	}
	private:
		string s;
};
#endif
