#include "db_mysql.h"

int main()
{
	DB_MYSQL mysql;
	MysqlRecordset mrs;

	try
	{
		cout<<"connect to mysql..."<<endl;
		mysql.connect("10.200.1.118", "root", "123456", "eshowdb", 3306);
		cout<<"query   to mysql..."<<endl;
		mrs = mysql.query("select * from es_host");

		cout<<"get result from mysql..."<<endl;
		string s;
		for(int i=0; i<mrs.GetRows(); i++)
		{
			for(int j=0; j<mrs.GetCols(); j++)
			{
				s = mrs.GetItem(i, j);
				cout<<"i="<<i<<" j="<<j<<" and s="<<s<<endl;
			}
		}
		s = mrs.GetItem(1,"vc_host_name");
		cout<<"Get host name = "<<s<<endl;

		s = mrs.GetItem(-1,"vc_host_name");
		cout<<"Get host name = "<<s<<endl;
	}
	catch(DBException e){
	cout<<"exception mysql..."<<endl;
		e.p();
	}
	catch(exception e){
		cout<<e.what()<<endl;;
	}
	catch(...)
	{
		cout<<"catch unexpect exception ..."<<endl;
	}
	
	cout<<"exit mysql..."<<endl;
	return 0;
}
