#/* High Score Saving Implementation */
import sys
import os
from highScoreStrings import *
from sharedVars import *
hssImpl_fileName = "highScore.5hs"
#/*
#Why can't I use ' to convert a character to its ASCII code?
#- StevenSYS 07/10/2025 (MM/DD/YYYY) 10:45 PM (UTC)
#*/
hssImpl_signature = bytearray([ord("5"), ord("H"), ord("S"), 0x57, 0xE6, 0xE4, 0x56, 0x50])
hssImpl_lengthBuffer = 20
#/* Enum - hssImpl_fileStatus */
FILE_NONE = 0
FILE_NEWFILE = 1
FILE_BROKEN = 2
#/* Enum End */
fileStatus = FILE_NONE
file = NULL
def hssImpl_get():
    #/*
    #This is the last function to implement
    #- StevenSYS 07/10/2025 (MM/DD/YYYY) 11:44 PM (UTC)
    #*/
    newScore = 0
    minSize = len(hssImpl_signature) + 1
    maxSize = len(hssImpl_signature) + 4
    fileSize = os.path.getsize(hssImpl_fileName)
    if (file.read().startswith(hssImpl_signature)):
        if (fileSize < minSize):
            print(
                HSSIMPL_STRING_FILE_WRONGSIZE1 +
                str(fileSize) +
                HSSIMPL_STRING_FILE_WRONGSIZE2 +
                str(minSize) +
                HSSIMPL_STRING_FILE_WRONGSIZE3
                )
            return 0
        elif (fileSize > maxSize):
            print(
                HSSIMPL_STRING_FILE_WRONGSIZE1 +
                str(fileSize) +
                HSSIMPL_STRING_FILE_WRONGSIZE2 +
                str(maxSize) +
                HSSIMPL_STRING_FILE_WRONGSIZE3
                )
            return 0
        else:
            #/*
            #I think Python might be the worst coding language ever created
            #- StevenSYS 07/14/2025 (MM/DD/YYYY) 12:30 PM (UTC)
            #*/
            file.seek(len(hssImpl_signature))
            for i in range(fileSize - len(hssImpl_signature)):
                newScore += ord(file.read(1)) << i * 8
    else:
        print(HSSIMPL_STRING_FILE_NOTVALID, file = sys.stderr)
        fileStatus = FILE_BROKEN
    return newScore
def hssImpl_set(highScore):
    #/*
    #I'm going to bed now, because it's 11 PM
    #By the way, I'm not removing these useless comments
    #Also I hate Python
    #- StevenSYS 07/09/2025 (MM/DD/YYYY) 11:17 PM (UTC)
    #*/
    #/*
    #All right, I'm back the next day to (hopefully) finish this!
    #- StevenSYS 07/10/2025 (MM/DD/YYYY) 10:28 PM (UTC)
    #*/
    #/*
    #I couldn't finish the HSS yesterday
    #Anyway, I'm going to bed now
    #Also I still hate Python
    #- StevenSYS 07/11/2025 (MM/DD/YYYY) 12:54 AM (UTC)
    #*/
    if (fileStatus == FILE_BROKEN):
        print(HSSIMPL_STRING_FILE_NOTVALID, file = sys.stderr)
    try:
        file = open(hssImpl_fileName, "wb+")
    except FileNotFoundError:
        print(HSSIMPL_STRING_FAILOPEN_WBPMODE, file = sys.stderr)
    else:
        file.write(hssImpl_signature)
        print(len(str(highScore)))
        for i in range(len(str(highScore))):
            if (highScore >= 5):
                break
            file.write(bytearray([highScore >> (i * 8) & 0xFF]))
        file.flush()
    return
def hssImpl_open():
    global file
    #/*
    #I hate using "try" and "except", it's like I'm using that terrible version of C called C++
    #- StevenSYS 07/09/2025 (MM/DD/YYYY) 10:50 PM (UTC)
    #*/
    try:
        open(hssImpl_fileName, "rb")
        #/*
        #Why does removing the space from "} except" fix it not working?
        #- StevenSYS 07/09/2025 (MM/DD/YYYY) 11:02 PM (UTC)
        #*/
    except FileNotFoundError:
        #/*
        #Why don't "printf" or "fprintf" work?
        #- StevenSYS 07/09/2025 (MM/DD/YYYY) 10:38 PM (UTC)
        #*/
        print(HSSIMPL_STRING_FILE_FAILOPEN_RMODE)
        try:
            #/*
            #I typed in "fopen" instead of "open" at first
            #- StevenSYS 07/09/2025 (MM/DD/YYYY) 11:06 PM (UTC)
            #*/
            file = open(hssImpl_fileName, "wb+")
        except FileNotFoundError:
            print(HSSIMPL_STRING_FILE_FAILOPEN_WBOPMODE, file = sys.stderr)
        else:
            fileStatus = FILE_NEWFILE
            hssImpl_set(0)
    else:
        try:
            file = open(hssImpl_fileName, "rb+")
        except FileNotFoundError:
            print(HSSIMPL_STRING_FILE_FAILOPEN_RBPMODE, file = sys.stderr)
    return
def hssImpl_close():
    global file
    file.close()
    #/*
    #Why doesn't "!" work?
    #- StevenSYS 07/09/2025 (MM/DD/YYYY) 11:11 PM (UTC)
    #*/
    if (not file.closed):
        print(HSSIMPL_STRING_FILE_NOTINIT, file = sys.stderr)
    return
