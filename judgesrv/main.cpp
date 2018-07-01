#include <QCoreApplication>
// #include <QTcpSocket>
#include <QUdpSocket>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

QUdpSocket sock;
QTextStream ts;
QDataStream ds;

#define printf(x...) fprintf(stderr, x)

size_t fileSize(const char *fn)
{
	struct stat st;
	if(stat(fn, &st))
		return 0;
	return st.st_size;
}

void sendFile(const char *sfn, const char *tfn)
{
	printf("send %s -> %s\n", sfn, tfn);
	string fn = string("f") + tfn;
	ts << fn.c_str();
	ts.flush();
	sock.waitForReadyRead();
	qDebug() << ts.readAll();
	int sz = fileSize(sfn);
	char *fileAll = new char[sz];
	FILE *fin = fopen(sfn, "rb");
	fread(fileAll, 1, sz, fin);
	fclose(fin);
	
	typedef pair<int, int> pii; // (off, len)
	set<pii> todo;
	for(int i = 0; i < sz; i += 500)
		todo.insert(pii(i, min(sz - i, 500)));
	
	char buf[512];
	while(todo.size())
	{
		for(pii p: todo)
		{
			memcpy(buf + 4, &p.first, 4);
			memcpy(buf + 8, fileAll + p.first, p.second);
			buf[0] = 'g';
			buf[1] = 'g';
			buf[2] = 'g';
			buf[3] = 'g';
			ds.writeRawData(buf, p.second + 4);
			sock.flush();
		}
		while(sock.waitForReadyRead(1000))
		{
			int len = sock.readDatagram(buf, sizeof(buf));
			if(buf[0] != 'a') continue;
			int off; memcpy(&off, buf[4], 4);
			auto it = todo.lower_bound(pii(off, 0));
			if(it != todo.end() && it->first == off) todo.erase(it);
			if(!todo.size()) break;
		}
	}
	ts << "e";
	ts.flush();
	sock.waitForReadyRead();
	qDebug() << ts.readAll();
	printf("send ok\n");
	delete[] fileAll;
}
void runCmd(string cmd)
{
	printf("runCmd %s\n", cmd.c_str());
	cmd = "c" + cmd;
	ts << cmd.c_str();
	ts.flush();
	sock.waitForReadyRead();
	qDebug() << ts.readAll();
	printf("runCmd ok\n");
}
QString fileContent(string fn)
{
	printf("fileContent %s\n", fn.c_str());
	fn = "o" + fn;
	ts << fn.c_str();
	ts.flush();
	sock.waitForReadyRead();
	printf("fileContent ok\n");
	return ts.readAll();
}

// fn = ***.c
QString judgeFile(const char *fn)
{
	size_t sz = fileSize(fn);
	if(sz <= 0) return "source too small";
	if(sz >= 10000) return "source too large";
	string cmd = string("rm -f /home/yjp/OS2018spring-projects-g04/obj/user/judging && cp ") + fn + " /home/yjp/OS2018spring-projects-g04/user/judging.c && make -C /home/yjp/OS2018spring-projects-g04/ obj/user/judging > /dev/null";
	int r = system(cmd.c_str());
	if(r) return "compile error";
	
	sz = fileSize("/home/yjp/OS2018spring-projects-g04/obj/user/judging");
	if(sz <= 0) return "binary too small";
	if(sz >= 131072) return "binary too large";
	
	qDebug() << sock.bind("10.0.2.2", 8008);
	sock.connectToHost("10.0.2.15", 80);
	sock.waitForConnected();
	ts.setDevice(&sock);
	ds.setDevice(&sock);
	
	sendFile("/home/yjp/OS2018spring-projects-g04/obj/user/judging", "judging");
	runCmd("arbiter judging 5000 65536 1 10000 > arbiter.out");
	return fileContent("arbiter.out");
}

int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);

	QTextStream qout(stdout);
	
	qout << judgeFile(argv[1]);
	
	return 0;
}

