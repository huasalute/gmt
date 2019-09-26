/*
 * Copyright (c) 2016-2019 by the GMT Team (https://www.generic-mapping-tools.org/team.html)
 * See LICENSE.TXT file for copying and redistribution conditions.
 */

/* gmt_mbsystem_module.c populates the local array g_mbsystem_module
 * with parameters such as name, group, purpose and keys strings.
 * This file also contains the following convenience functions to
 * display all module purposes or just list their names:
 *
 *   void gmt_mbsystem_module_show_all (void *API);
 *   void gmt_mbsystem_module_list_all (void *API);
 *
 * These functions may be called by gmt --help and gmt --show-modules
 *
 * DO NOT edit this file directly! Regenerate the file by running
 *	 gmt_make_custom_code.sh mbsystem
 */

#include "gmt.h"
#include "gmt_mbsystem_module.h"
#include <string.h>

#ifndef gmt_M_unused
#define gmt_M_unused(x) (void)(x)
#endif

/* Sorted array with information for all mbsystem modules */

/* name, library, and purpose for each module */
struct Gmt_moduleinfo {
	const char *name;             /* Program name */
	const char *component;        /* Component (core, supplement, custom) */
	const char *purpose;          /* Program purpose */
	const char *keys;             /* Program option info for external APIs */
};

static struct Gmt_moduleinfo g_mbsystem_module[] = {
	{"mbcontour", "mbgmt",  "Plot swath bathymetry, amplitude, or backscatter",  ""},
	{"mbgrdtiff", "mbgmt",  "Project grids or images and plot them on maps",  ""},
	{"mbswath", "mbgmt",  "Plot swath bathymetry, amplitude, or backscatter",  ""},
	{NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */
};

/* Pretty print all GMT mbsystem module names and their purposes for gmt --help */
void gmt_mbsystem_module_show_all (void *V_API) {
	unsigned int module_id = 0;
	char message[256] = {""};
	GMT_Message (V_API, GMT_TIME_NONE, "\n===  mbsystem modules accessible from gmt  ===\n");
	while (g_mbsystem_module[module_id].name != NULL) {
		if (module_id == 0 || strcmp (g_mbsystem_module[module_id-1].component, g_mbsystem_module[module_id].component)) {
			/* Start of new supplemental group */
			snprintf (message, 256, "\nModule name:     Purpose of %s module:\n", g_mbsystem_module[module_id].component);
			GMT_Message (V_API, GMT_TIME_NONE, message);
			GMT_Message (V_API, GMT_TIME_NONE, "----------------------------------------------------------------\n");
		}
	snprintf (message, 256, "%-16s %s\n",
		g_mbsystem_module[module_id].name, g_mbsystem_module[module_id].purpose);
		GMT_Message (V_API, GMT_TIME_NONE, message);
		++module_id;
	}
}

/* Produce single list on stdout of all GMT mbsystem module names for gmt --show-modules */
void gmt_mbsystem_module_list_all (void *API) {
	unsigned int module_id = 0;
	gmt_M_unused(API);
	while (g_mbsystem_module[module_id].name != NULL) {
		printf ("%s\n", g_mbsystem_module[module_id].name);
		++module_id;
	}
}

/* Lookup module id by name, return option keys pointer (for external API developers) */
const char *gmt_mbsystem_module_keys (void *API, char *candidate) {
	int module_id = 0;
	gmt_M_unused(API);

	/* Match actual_name against g_module[module_id].name */
	while (g_mbsystem_module[module_id].name != NULL &&
	       strcmp (candidate, g_mbsystem_module[module_id].name))
		++module_id;

	/* Return Module keys or NULL */
	return (g_mbsystem_module[module_id].keys);
}

/* Lookup module id by name, return group char name (for external API developers) */
const char *gmt_mbsystem_module_group (void *API, char *candidate) {
	int module_id = 0;
	gmt_M_unused(API);

	/* Match actual_name against g_module[module_id].name */
	while (g_mbsystem_module[module_id].name != NULL &&
	       strcmp (candidate, g_mbsystem_module[module_id].name))
		++module_id;

	/* Return Module keys or NULL */
	return (g_mbsystem_module[module_id].component);
}
