
/*
 *     xDMS -  Portable DMS archive unpacker - Public Domain
 *     Written by     Andre Rodrigues de la Rocha  <adlroc@usa.net>
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>

#include "cdata.h"
#include "pfile.h"
#include "crc_csum.h"
#include "xdmsconfig.h"

#ifdef UNDER_DOS
#include <io.h>
#include <fcntl.h>
#endif


#define FNAME_MAXC 512

/*
static void Usage(void);
static int strcmpnc(char *, char *);
static void strcpymax(char *, char *, int);
static void strcatmax(char *, char *, int);
static void ErrMsg(USHORT, char *, char *);
*/

#if 0
int main(int argc, char **argv){
    USHORT i, cmd=0, opt=0, ret, PCRC=0, pwd=0;
    int ext;
    char iname[FNAME_MAXC+1], oname[FNAME_MAXC+1], cmdstr[FNAME_MAXC+20], *inm, *onm, *p, *q, *destdir=NULL;
    char tname[FNAME_MAXC];


    if (argc < 3) {
        Usage();
        exit(EXIT_FAILURE);
    }

    /*  proccess options in the command line  */
    for (i=1; (i<argc) && (argv[i][0] == '-'); i++){
        if (strlen(argv[i])>2) {
            Usage();
            exit(EXIT_FAILURE);
        }
        switch (tolower(argv[i][1])) {
        case 'f':
            OverrideErrors = 1;
            break;
        case 'q' :
            opt = OPT_QUIET;
            break;
        case 'v' :
            opt = OPT_VERBOSE;
            break;
        case 'd' :
            if (++i == argc) {
                Usage();
                exit(EXIT_FAILURE);
            }
            destdir = argv[i];
            break;
        case 'p' :
            if (++i == argc) {
                Usage();
                exit(EXIT_FAILURE);
            }
            PCRC = CreateCRC((UCHAR*)argv[i],(ULONG)strlen(argv[i]));
            pwd = 1;
            break;
        default:
            Usage();
            exit(EXIT_FAILURE);
        }
    }

    if ((i == argc) || (strlen(argv[i])>1)) {
        Usage();
        exit(EXIT_FAILURE);
    }


    switch (tolower(argv[i][0])) {
        case 'u':
            cmd = CMD_UNPACK;
            break;
        case 'z':
            cmd = CMD_UNPKGZ;
            break;
        case 'x':
            cmd = CMD_EXTRACT;
            break;
        case 't':
            cmd = CMD_TEST;
            break;
        case 'v':
            cmd = CMD_VIEW;
            break;
        case 'f':
            cmd = CMD_VIEWFULL;
            break;
        case 'd':
            cmd = CMD_SHOWDIZ;
            break;
        case 'b':
            cmd = CMD_SHOWBANNER;
            break;
        default:
            Usage();
            exit(EXIT_FAILURE);
    }

    if (++i == argc) {
        Usage();
        exit(EXIT_FAILURE);
    }

    ext = EXIT_SUCCESS;

    while (i < argc) {

        if (!strcmpnc("stdin",argv[i])) {
            inm = NULL;
        } else {
            strcpymax(iname,argv[i],FNAME_MAXC);
            if ((strlen(iname)<4) || (strcmpnc(".dms",iname+strlen(iname)-4))) strcatmax(iname,".dms",FNAME_MAXC);
            inm = iname;
        }
        i++;


        /*  generate the output filename  */
        if ((i < argc) && (argv[i][0]=='+')) {
            if ((!strcmpnc("stdout",argv[i]+1)) || (destdir && (!strcmpnc("stdout",destdir)))) {
                strcpy(oname,"");
                onm = NULL;
            } else {
                if (destdir) {
                    strcpymax(oname,destdir,FNAME_MAXC-1);
                    p = oname + strlen(oname) - 1;
                    if (!strchr(DIR_SEPARATORS,*p)) {
                        *(p+1) = DIR_CHAR;
                        *(p+2) = '\0';
                    }
                } else strcpy(oname,"");
                strcatmax(oname,argv[i]+1,FNAME_MAXC);
                if (((cmd == CMD_UNPACK) || (cmd == CMD_UNPKGZ)) && (strlen(oname)>0)) {
                    p = oname + strlen(oname) - 1;
                    if (strchr(DIR_SEPARATORS,*p)) {
                        if (inm) {
                            p = q = iname;
                            while(*p) {
                                if (strchr(DIR_SEPARATORS,*p)) q = p+1;
                                p++;
                            }
                            strcatmax(oname,q,FNAME_MAXC);
                            if ((strlen(oname)>4) && (!strcmpnc(oname+strlen(oname)-4,".dms"))) {
                                if (cmd == CMD_UNPKGZ)
                                    strcpy(oname+strlen(oname)-4,".adz");
                                else
                                    strcpy(oname+strlen(oname)-4,".adf");
                            } else {
                                if (cmd == CMD_UNPKGZ)
                                    strcatmax(oname,".adz",FNAME_MAXC);
                                else
                                    strcatmax(oname,".adf",FNAME_MAXC);
                            }
                        } else {
                            if (cmd == CMD_UNPKGZ)
                                strcatmax(oname,"stdin.adz",FNAME_MAXC);
                            else
                                strcatmax(oname,"stdin.adf",FNAME_MAXC);
                        }

                    }
                }

                onm = oname;
            }
            i++;
        } else if (destdir && (!strcmpnc("stdout",destdir))) {
            strcpy(oname,"");
            onm = NULL;
        } else {

            if (destdir)
                strcpymax(oname,destdir,FNAME_MAXC-1);
            else
                strcpy(oname,"");

            if ((cmd == CMD_UNPACK) || (cmd == CMD_UNPKGZ)) {

                if (strlen(oname)>0) {
                    p = oname + strlen(oname) - 1;
                    if (!strchr(DIR_SEPARATORS,*p)) {
                        *(p+1) = DIR_CHAR;
                        *(p+2) = '\0';
                    }
                }

                if (inm) {
                    p = q = iname;
                    while(*p) {
                        if (strchr(DIR_SEPARATORS,*p)) q = p+1;
                        p++;
                    }
                    strcatmax(oname,q,FNAME_MAXC);
                    if ((strlen(oname)>4) && (!strcmpnc(oname+strlen(oname)-4,".dms"))) {
                        if (cmd == CMD_UNPKGZ)
                            strcpy(oname+strlen(oname)-4,".adz");
                        else
                            strcpy(oname+strlen(oname)-4,".adf");
                    } else {
                        if (cmd == CMD_UNPKGZ)
                            strcatmax(oname,".adz",FNAME_MAXC);
                        else
                            strcatmax(oname,".adf",FNAME_MAXC);
                    }
                } else {
                    if (cmd == CMD_UNPKGZ)
                        strcatmax(oname,"stdin.adz",FNAME_MAXC);
                    else
                        strcatmax(oname,"stdin.adf",FNAME_MAXC);
                }

            }

            onm = oname;

        }



        #ifdef UNDER_DOS
        if (!inm) setmode(fileno(stdin),O_BINARY);
        if ((cmd == CMD_UNPACK) && (!onm)) setmode(fileno(stdout),O_BINARY);
        #endif

        if ((cmd == CMD_UNPKGZ) || (cmd == CMD_EXTRACT)) {
            int fd;
            strcpy(tname, "/tmp/xdmsXXXXXX");
            fd = mkstemp(tname);
            if (fd < 0) {
                exit(-1);
            }
            close(fd);
            #ifdef UNDER_DOS
            p = tname;
            if (p) {
                while (*p) {
                    if (*p == '/') *p = '\\';
                    p++;
                }
            }
            #endif
            ret = Process_File(inm, tname, CMD_UNPACK, opt, PCRC, pwd);
            if (opt != OPT_QUIET) ErrMsg(ret, inm, "Temporary file");
            if (ret == NO_PROBLEM) {
                if (cmd == CMD_UNPKGZ) {
                    if (system(cmdstr)) ret = ERR_GZIP;
                    if (opt != OPT_QUIET) ErrMsg(ret, inm, onm);
                } else {
                    if (system(cmdstr)) ret = ERR_READDISK;
                    if (opt != OPT_QUIET) ErrMsg(ret, inm, onm);
                }
            }
            remove(tname);
        } else {
            ret = Process_File(inm, onm, cmd, opt, PCRC, pwd);
            if (opt != OPT_QUIET) ErrMsg(ret, inm, onm);
        }

        if (ret != NO_PROBLEM) ext = EXIT_FAILURE;

    }

    return (int) ext;
}
#endif

#if 0
static int strcmpnc(char *s1, char *s2){
    while (*s1 && (tolower(*s1)==tolower(*s2))) {s1++; s2++;}
    return tolower(*s1)-tolower(*s2);
}



static void strcpymax(char *s1, char *s2, int max){
    if (strlen(s2)>max){
        memcpy(s1,s2,max);
        *(s1+max) = 0;
    } else
        strcpy(s1,s2);
}



static void strcatmax(char *s1, char *s2, int max){
    if (strlen(s1)+strlen(s2)>max){
        memcpy(s1+strlen(s1),s2,max-strlen(s1));
        *(s1+max) = 0;
    } else
        strcat(s1,s2);
}



static void Usage(void)
{
}



static void ErrMsg(USHORT err, char *i, char *o){
}
#endif
