
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

#include "../../lsMisc/CommandLineParser.h"
#include "../../lsMisc/UTF16toUTF8.h"
#include "../../lsMisc/stdwin32/stdwin32.h"

#define HAVE_IMAGE_HASH
#define HAVE_VIDEO_HASH
#include <pHash.h>
#include "SQLiteCpp/Database.h"

using namespace Ambiesoft;
using namespace std;
using namespace stdwin32;

void aaa()
{
	try
	{
		// Open a database file
		SQLite::Database    db("example.db3");

		// Compile a SQL query, containing one parameter (index 1)
		SQLite::Statement   query(db, "SELECT * FROM test WHERE size > ?");

		// Bind the integer value 6 to the first parameter of the SQL query
		query.bind(1, 6);

		// Loop to execute the query step by step, to get rows of result
		while (query.executeStep())
		{
			// Demonstrate how to get some typed column value
			int         id = query.getColumn(0);
			const char* value = query.getColumn(1);
			int         size = query.getColumn(2);

			std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
		}
	}
	catch (std::exception & e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}
}
int main2(int argc, char **argv)
{
	CCommandLineParserW parser;

	bool dct = false;
	parser.AddOption(L"/dct", 0, &dct, ArgEncodingFlags_Default, L"dct method");

	bool decimal = false;
	parser.AddOption(L"/decimal", 0, &decimal, ArgEncodingFlags_Default, L"decimal output");

	bool image = true;
	parser.AddOption(L"/image", 0, &image, ArgEncodingFlags_Default, L"image hash");

	bool video = false;
	parser.AddOption(L"/video", 0, &video, ArgEncodingFlags_Default, L"video hash");

	bool help = false;
	parser.AddOption(L"/h", 0, &help, ArgEncodingFlags_Default, L"show help");
	
	wstring dbFile;
	parser.AddOption(L"/od", 1, &dbFile, ArgEncodingFlags_Default, L"database to write");

	INT64 id = -1;
	parser.AddOption(L"/id", 1, &id, ArgEncodingFlags_Default, L"specify id");

	wstring file;
	parser.AddOption(L"", 1, &file, ArgEncodingFlags_Default, L"specify file to calculate hash");


	parser.Parse();

	if (help)
	{
		wcout << parser.getHelpMessage() << endl;
		return 0;
	}
	
	unique_ptr<SQLite::Database> db;
	if (!dbFile.empty())
	{
		// prepare database
		db.reset(new SQLite::Database(toStdUtf8String(dbFile).c_str(),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE));
		if(!db.get()->tableExists("phash"))
			db.get()->exec("CREATE TABLE phash (id INTEGER, hashindex INTEGER, value INTEGER)");
	}

	if (file.empty())
	{
		wcerr << L"specify file" << endl;
		return 1;
	}
	
	if (dct)
	{
		if (video)
		{
			int length = 0;
			ulong64* hash = ph_dct_videohash(toStdUtf8String(file).c_str(), length);
			if (!hash)
			{
				wcerr << "ph_dct_videohash failed" << endl;
				return 1;
			}
			if (length == 0)
			{
				wcerr << "ph_dct_videohash's length = 0" << endl;
				return 1;
			}
			if(db)
			{
				stringstream sql;
				sql << "INSERT INTO phash (id,hashindex,value) VALUES ";
				for (int i = 0; i < length; ++i)
				{
					sql << "(" << id << "," << i << "," << hash[i] << ")";
					if ((i + 1) != length)
						sql << ",";
				}
				sql << ";";
				
				int nb = db.get()->exec(sql.str().c_str());
				std::cout << sql.str().c_str() << " returned " << nb << std::endl;
			}
			else
			{
				// write to stdout
				for (int i = 0; i < length; ++i)
				{
					wcout << hash[i];
					if ((i + 1) != length)
						wcout << L" ";
				}
				wcout << endl;
			}
		}
	}
	return 0;
}

int main(int argc,char** argv)
{
	try
	{
		return main2(argc, argv);
	}
	catch (std::exception & e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}
	return 1;
}
//int main_old(int argc, char **argv) {
//	if (argc >= 3 && stricmp(argv[1], "/dct-decimal") == 0) {
//		ulong64 hash;
//		if (0 == ph_dct_imagehash(argv[2], hash)) {
//			printf("%I64u", hash);
//			return 0;
//		}
//		return 1;
//	}
//	if (argc >= 3 && stricmp(argv[1], "/dct") == 0) {
//		ulong64 hash;
//		if (0 == ph_dct_imagehash(argv[2], hash)) {
//			printf("%16I64x", hash);
//			return 0;
//		}
//		return 1;
//	}
//	else if (argc >= 3 && stricmp(argv[1], "/mh-decimal") == 0) {
//		int cx = 0;
//		uint8_t *hash = ph_mh_imagehash(argv[2], cx,
//			(argc >= 4) ? (float)strtod(argv[3], NULL) : 2.0f,
//			(argc >= 5) ? (float)strtod(argv[4], NULL) : 1.0f
//		);
//		if (hash != NULL) {
//			for (int x = 0; x < cx; x++) {
//				if (x != 0) {
//					putchar(' ');
//				}
//				printf("%u", hash[x]);
//			}
//			return 0;
//		}
//		return 1;
//	}
//	else if (argc >= 3 && stricmp(argv[1], "/mh") == 0) {
//		int cx = 0;
//		uint8_t *hash = ph_mh_imagehash(argv[2], cx,
//			(argc >= 4) ? (float)strtod(argv[3], NULL) : 2.0f,
//			(argc >= 5) ? (float)strtod(argv[4], NULL) : 1.0f
//		);
//		if (hash != NULL) {
//			for (int x = 0; x < cx; x++) {
//				printf("%02x", hash[x]);
//			}
//			return 0;
//		}
//		return 1;
//	}
//	fprintf(stderr,
//		"RunpHash /dct         <image.png or image.jpg>\n"
//		"RunpHash /dct-decimal <image.png or image.jpg>\n"
//		"RunpHash /mh          <image.png or image.jpg> (<alpha> (<level>))\n"
//		"RunpHash /mh-decimal  <image.png or image.jpg> (<alpha> (<level>))\n"
//	);
//	return 1;
//}
