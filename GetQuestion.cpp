/*
    License

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Copyright(c) (2016-2020) Steve Chekblain
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
bool ask[10000];
int qnum = 0, badseed = 0;

void ThrowExecption(int errcode)
{
	char* stmp = "";
	switch (errcode) {
		case 101:
			stmp = "Bad Arguments!";
		break;
		case 102:
			stmp = "All Questions Had Been Asked!";
		break;
		case 103:
			stmp = "Unable To Read \"ask.dat\"!";
		break;
		case 104:
			stmp = "Unable To Write \"ask.dat\"!";
		break;
		case 105:
			stmp = "Unable To Write \"question.txt\"!";
		break;
		case 106:
			stmp = "Unable To Read Question File!";
		break;
		case 107:
			stmp = "";
		break;
		case 108:
			stmp = "";
		break;
	}
	printf("ERROR %d: %s\n", errcode, stmp);
	exit(errcode);
}

void ReadStatus(bool check)
{
	memset(ask, false, sizeof(ask));
	FILE* inp = fopen("ask.dat", "r");
	if (!inp) ThrowExecption(103);
    fscanf(inp, "%d", &qnum);
    int tmp;
    while (fscanf(inp, "%d", &tmp) != -1)
        if (tmp > 0 && tmp < qnum) ask[tmp] = true;
    bool flag = check;
    for (int i = 1; i <= qnum; i++) flag &= ask[i];
    fclose(inp);
    if (flag) ThrowExecption(102);
    badseed *= tmp * qnum + time(NULL);
}

void PrintQuestion(int qno, bool record)
{
    char stmp[10000] = "";
    sprintf(stmp, "t\\t%04d.txt", qno);
    FILE *inp = fopen(stmp, "r"), *oup = fopen("ask.dat", "a");
    if (!inp) ThrowExecption(106);
    if (!oup) ThrowExecption(104);
    if (record) fprintf(oup, "%d\n", qno);
    fclose(oup);
    oup = fopen("question.txt", "w");
    if(!oup) ThrowExecption(105);
    while (fgets(stmp, 500, inp))
        fprintf(oup, "%s", stmp);
    fclose(inp);
    fclose(oup);
    exit(0);
}

int GetRandom(bool check)
{
    int tmp = rand() % qnum + 1;
    while (ask[tmp] && check) tmp = rand() % qnum + 1;
    printf("%d\n", tmp);
    return tmp;
}

void ResetStatus()
{
    char stmp[10000] = "";
    FILE* inp;
    while (1) {
        qnum++;
        sprintf(stmp, "t\\t%04d.txt", qnum);
        inp = fopen(stmp, "r");
        if (!inp) break;
        fclose(inp);
    }
    qnum--;
    fclose(inp);
    inp = fopen("ask.dat", "w");
    if (!inp) ThrowExecption(104);
    fprintf(inp, "%d\n", qnum);
    for (int i = 1; i <= qnum; i++)
        if (ask[i]) fprintf(inp, "%d\n", i);
    fclose(inp);
    inp = fopen("ask.dat", "r");
    if (!inp) ThrowExecption(103);
}

void CheckArguments(char* arg)
{
	if (arg[0] != '-') ThrowExecption(101);
    if (arg[1] == 'r' && !arg[2]) {
        ResetStatus();
        exit(0);
    }
    if (arg[1] == 'q' && !arg[2]) {
    	ReadStatus(true);
        PrintQuestion(GetRandom(true), false);
        exit(0);
    }
    if (arg[1] == 'c' && !arg[2]) {
    	ReadStatus(false);
        PrintQuestion(GetRandom(false), true);
        exit(0);
    }
    if (arg[1] == 'c' && arg[2] == 'q' && !arg[3]) {
    	ReadStatus(false);
        PrintQuestion(GetRandom(false), false);
        exit(0);
    }
    ThrowExecption(101);
}

int main(int argc, char* argv[])
{
    badseed = (unsigned)time(NULL);
    if (argc == 1) {
    	ReadStatus(true);
	    PrintQuestion(GetRandom(true), true);
	}
    else CheckArguments(argv[1]);
    return 0;
}

