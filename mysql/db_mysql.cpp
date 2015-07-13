#include <stdlib.h>
#include <string.h>
#include "db_mysql.h"

int MysqlRecordset::GetFieldIndex(const string& name) const
{
	int index = -1;
	for(int i = 0; i < fields.size(); i++)
	{
		if(fields[i].name == name)
		{
			index = i;
		}
	}
	if(index < 0){
		throw DBException("Can't find column " + name);
	}
	else
	{
		return index;
	}
}

DB_MYSQL::DB_MYSQL()
{
}

DB_MYSQL::~DB_MYSQL()
{
	if(mysql){
		disconnect();
	}
}

void DB_MYSQL::connect(const char* host, 
				  const char* user, 
				  const char* passwd, 
				  const char*db_name, 
				  unsigned int port)
{
	mysql = mysql_init(NULL);
	if(mysql == NULL)
	{
		string errMsg = mysql_error(mysql);
		throw DBException("mysql init error:" + errMsg);
	}
	if(!mysql_real_connect(mysql, host, user, passwd, db_name, port, NULL, 0))
	{
		string errMsg = mysql_error(mysql);
		disconnect();
		throw DBException("mysql connect error:" + errMsg);
	}
}

void DB_MYSQL::disconnect()
{
	if(mysql != NULL)
	{
		mysql_close(mysql);
		mysql = NULL;
	}
}

MysqlRecordset DB_MYSQL::query(const char* sql)
{
	int ret = 0;
	ret = mysql_real_query(mysql, sql, (unsigned int)strlen(sql));

	if(ret)
	{
		string errMsg = mysql_error(mysql);
		throw DBException("mysql error:" + errMsg);
	}

	MysqlRecordset rs ;
	MysqlRecordset::FIELD fd ;
	MysqlRecordset::ROW r ;
	MYSQL_FIELD* mysql_field = NULL;
	MYSQL_RES *res;

	res = mysql_store_result(mysql);

	unsigned int i = 0;
	while((mysql_field = mysql_fetch_field(res)) != NULL)
	{
		fd.index = i;
		fd.name = mysql_field->name;
		rs.fields.push_back(fd);
		i++;
		cout<<"i = "<<i<<endl;
	}
	cout<<"fetch row "<<endl;

	int nCols = mysql_num_fields(res);
	MYSQL_ROW row;
	string str;
	while((row = mysql_fetch_row(res)) != NULL)
	{
		for(int t = 0; t < i; t++)
		{
			//cout<<"t = "<<t<<" and row="<<row[t]<<endl;
			//r[t] = row[t];
			if(row[t] == NULL)
			{
				str = "NULL";
			}
			else
			{
				str = row[t];
			}
			cout<<"t = "<<t<<" and row="<<str<<endl;
			r.push_back(str);
		}
		cout<<"get one row."<<endl;
		rs.rows.push_back(r);
		r.clear();
	}

	mysql_free_result(res);
	return rs;
}

int DB_MYSQL::execSQL(const char* sql)
{
	if(mysql_real_query(mysql, sql, (unsigned int)strlen(sql)) <0)
	{
		string errMsg = mysql_error(mysql);
		throw DBException("mysql error:" + errMsg);
	}
	return mysql_affected_rows(mysql);	
}
