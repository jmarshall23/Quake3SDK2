/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
#include "g_local.h"

gameImport_t* gameSyscall;
gameExport_t* game;

void G_InitGame(int levelTime, int randomSeed, int restart);
void G_ShutdownGame(int restart);
void G_RunFrame(int levelTime);

gameExport_t *dllEntry(gameImport_t* gameAPI) {
    static gameExport_t exports;

    exports.G_InitGame = G_InitGame;
    exports.G_ShutdownGame = G_ShutdownGame;
    exports.ClientConnect = ClientConnect;
    exports.ClientThink = ClientThink;
    exports.ClientUserinfoChanged = ClientUserinfoChanged;
    exports.ClientDisconnect = ClientDisconnect;
    exports.ClientBegin = ClientBegin;
    exports.ClientCommand = ClientCommand;
    exports.G_RunFrame = G_RunFrame;
    exports.ConsoleCommand = ConsoleCommand;

    gameSyscall = gameAPI;
    game = &exports;

    return &exports;
}
void trap_Printf(const char* fmt) {
    gameSyscall->Print(fmt);
}

void trap_Error(const char* fmt) {
    gameSyscall->Error(ERR_DROP, fmt);
}

int trap_Milliseconds(void) {
    return gameSyscall->Milliseconds();
}

void trap_Cvar_Register(vmCvar_t* cvar, const char* var_name, const char* value, int flags) {
    gameSyscall->Cvar_Register(cvar, var_name, value, flags);
}

void trap_Cvar_Update(vmCvar_t* cvar) {
    gameSyscall->Cvar_Update(cvar);
}

void trap_Cvar_Set(const char* var_name, const char* value) {
    gameSyscall->Cvar_Set(var_name, value);
}

int trap_Cvar_VariableIntegerValue(const char* var_name) {
    return gameSyscall->Cvar_VariableIntegerValue(var_name);
}

void trap_Cvar_VariableStringBuffer(const char* var_name, char* buffer, int bufsize) {
    gameSyscall->Cvar_VariableStringBuffer(var_name, buffer, bufsize);
}

int trap_Argc(void) {
    return gameSyscall->Argc();
}

void trap_Argv(int n, char* buffer, int bufferLength) {
    gameSyscall->Argv(n, buffer, bufferLength);
}

void trap_SendConsoleCommand(int exec_when, const char* text) {
    gameSyscall->SendConsoleCommand(exec_when, text);
}

int trap_FS_FOpenFile(const char* qpath, fileHandle_t* f, fsMode_t mode) {
    return gameSyscall->FS_FOpenFile(qpath, f, mode);
}

void trap_FS_Read(void* buffer, int len, fileHandle_t f) {
    gameSyscall->FS_Read(buffer, len, f);
}

void trap_FS_Write(const void* buffer, int len, fileHandle_t f) {
    gameSyscall->FS_Write(buffer, len, f);
}

void trap_FS_FCloseFile(fileHandle_t f) {
    gameSyscall->FS_FCloseFile(f);
}

int trap_FS_GetFileList(const char* path, const char* extension, char* listbuf, int bufsize) {
    return gameSyscall->FS_GetFileList(path, extension, listbuf, bufsize);
}

int trap_FS_Seek(fileHandle_t f, long offset, int origin) {
    return gameSyscall->FS_Seek(f, offset, origin);
}

void trap_LocateGameData(gentity_t* gEnts, int numGEntities, int sizeofGEntity_t, playerState_t* clients, int sizeofGClient) {
    gameSyscall->LocateGameData(gEnts, numGEntities, sizeofGEntity_t, clients, sizeofGClient);
}

void trap_DropClient(int clientNum, const char* reason) {
    gameSyscall->DropClient(clientNum, reason);
}

void trap_SendServerCommand(int clientNum, const char* text) {
    gameSyscall->SendServerCommand(clientNum, text);
}

void trap_SetConfigstring(int num, const char* string) {
    gameSyscall->SetConfigstring(num, string);
}

void trap_GetConfigstring(int num, char* buffer, int bufferSize) {
    gameSyscall->GetConfigstring(num, buffer, bufferSize);
}

void trap_GetUserinfo(int num, char* buffer, int bufferSize) {
    gameSyscall->GetUserinfo(num, buffer, bufferSize);
}

void trap_SetUserinfo(int num, const char* buffer) {
    gameSyscall->SetUserinfo(num, buffer);
}

void trap_GetServerinfo(char* buffer, int bufferSize) {
    gameSyscall->GetServerinfo(buffer, bufferSize);
}

void trap_SetBrushModel(gentity_t* ent, const char* name) {
    gameSyscall->SetBrushModel(ent, name);
}

void trap_Trace(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask) {
    gameSyscall->Trace(results, start, (vec_t *) mins, (vec_t*)maxs, end, passEntityNum, contentmask, qfalse);
}

void trap_TraceCapsule(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask) {
    gameSyscall->Trace(results, start, (vec_t*)mins, (vec_t*)maxs, end, passEntityNum, contentmask, qtrue);
}

int trap_PointContents(const vec3_t point, int passEntityNum) {
    return gameSyscall->PointContents(point, passEntityNum);
}

qboolean trap_InPVS(const vec3_t p1, const vec3_t p2) {
    return gameSyscall->inPVS(p1, p2);
}

qboolean trap_InPVSIgnorePortals(const vec3_t p1, const vec3_t p2) {
    return gameSyscall->inPVSIgnorePortals(p1, p2);
}

void trap_AdjustAreaPortalState(gentity_t* ent, qboolean open) {
    gameSyscall->AdjustAreaPortalState((sharedEntity_t *)ent, open);
}

qboolean trap_AreasConnected(int area1, int area2) {
    return gameSyscall->AreasConnected(area1, area2);
}

void trap_LinkEntity(gentity_t* ent) {
    gameSyscall->LinkEntity(ent);
}

void trap_UnlinkEntity(gentity_t* ent) {
    gameSyscall->UnlinkEntity(ent);
}

int trap_EntitiesInBox(const vec3_t mins, const vec3_t maxs, int* list, int maxcount) {
    return gameSyscall->EntitiesInBox(mins, maxs, list, maxcount);
}

qboolean trap_EntityContact(const vec3_t mins, const vec3_t maxs, const gentity_t* ent) {
    return gameSyscall->EntityContact((vec_t *)mins, (vec_t*)maxs, (const sharedEntity_t *)ent, qfalse);
}

qboolean trap_EntityContactCapsule(const vec3_t mins, const vec3_t maxs, const gentity_t* ent) {
    return gameSyscall->EntityContact((vec_t*)mins, (vec_t*)maxs, (const sharedEntity_t*)ent, qtrue);
}

void trap_GetUsercmd(int clientNum, usercmd_t* cmd) {
    gameSyscall->GetUsercmd(clientNum, cmd);
}

qboolean trap_GetEntityToken(char* buffer, int bufferSize) {
    return (qboolean)gameSyscall->GetEntityToken(buffer, bufferSize);
}

int trap_RealTime(qtime_t* qtime) {
    return gameSyscall->RealTime(qtime);
}
