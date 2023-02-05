/* See LICENSE file for copyright and license details. */
/* Constants */
#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 11;        /* vertical padding for statusbar */
static const int vertpadtab         = 33;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_always, showtab_auto, showtab_nmodes, showtab_never };
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */
static const unsigned int ulinepad	= 6;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 3;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=10",
                                        "Material Design Icons-Regular:size=10",
                                      };
static const unsigned int colorfultag    = 1;  /* 0 means use SchemeSel for selected tag */

// theme
static const char text[]        = "#bbbbbb";
//static const char black[]       = "#1e222a";
static const char black[]       = "#2e3440";
static const char gray2[]       = "#2e323a"; // unfocused window border
static const char gray3[]       = "#545862";
static const char gray4[]       = "#6d8dad";
static const char blue[]        = "#61afef";  // focused window border
static const char green[]       = "#98c379";
static const char red[]         = "#e06c75";
static const char orange[]      = "#caaa6a";
static const char yellow[]      = "#e5c07b";
static const char pink[]        = "#c678dd";
static const char col_borderbar[]  = "#1e222a"; // inner border

static const char *colors[][3]      = {
    /*               fg         bg         border   */
    //[TagFocus]         = { yellow, black, black },
    [SchemeStatus]     = { text,  black, black },
    [SchemeNorm]       = { gray3, black, gray2 },
    [SchemeSel]        = { gray4, blue,  gray4 },
    [TabSel]           = { blue, gray2,  black },
    [TabNorm]          = { gray3, black, black },
    [SchemeTag]        = { gray3, black, black },
    [SchemeTag1]       = { blue,  black, black },
    [SchemeTag2]       = { red,   black, black },
    [SchemeTag3]       = { yellow, black,black },
    [SchemeTag4]       = { green, black, black },
    [SchemeTag5]       = { pink,  black, black },
    [SchemeLayout]     = { green, gray2, black },
    [SchemeBtnFloat]   = { blue, black, black },
    [SchemeBtnSticky]  = { pink, black, black },
    [SchemeBtnPrev]    = { green, black, black },
    [SchemeBtnNext]    = { yellow, black, black },
    [SchemeBtnClose]   = { red, black, black },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "" };

static const int tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3,
                                  SchemeTag4, SchemeTag5
                                };

/* default layout per tags */
/* The first element is for all-tag view, following i-th element corresponds to */
/* tags[i]. Layout is referred using the layouts array index.*/
static int def_layouts[1 + LENGTH(tags)]  = { 2, 0, 2, 0, 0, 0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,   "spterm",       NULL,       0,            1,           -1 },
	{ "spterm",   NULL,       NULL,       0,            1,           -1 },
	{ NULL,   "spcalc",       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, "-e", "nvim", "-c", ":terminal", "-c", ":startinsert", NULL };
//const char *spterm[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
//const char *spterm[] = {TERMINAL, "-n", "spterm", "-g", "120x34", "-e", "nvim", "-c", ":terminal", "-c", ":startinsert", NULL };
const char *spterm[] = {TERMINAL, "-c", "spterm", "-g", "75x20", "-e", "nvim", "-c", ":terminal", "-c", ":startinsert", NULL };
//const char *spcalc[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcalc[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "nvim", "-c" ":terminal bc -lq", "-c", ":startinsert", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	//XK_Return
	{ MODKEY,                       36, 	 spawn,          {.v = termcmd } },
	//XK_b
	{ MODKEY,                       56,      togglebar,      {0} },
	//XK_w
	{ MODKEY,                       25,      tabmode,        {-1} },
	//XK_j
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	//XK_k
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	//XK_i
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	//XK_d
	{ MODKEY,                       40,      incnmaster,     {.i = -1 } },
	//XK_h
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	//XK_l
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	//XK_Tab
	{ MODKEY,                       23,    	 view,           {0} },
	//XK_x
	{ MODKEY,                       53,      killclient,     {0} },
	//XK_t
	{ MODKEY,                       28,      setlayout,      {.v = &layouts[0]} },
	//XK_f
	{ MODKEY,                       41,      setlayout,      {.v = &layouts[1]} },
	//XK_m
	{ MODKEY,                       58,      setlayout,      {.v = &layouts[2]} },
	//XK_r
        { MODKEY,                       27,      setlayout,      {.v = &layouts[3]} },
	//XK_space
	{ MODKEY,                       65,  	 zoom,           {0} },
	//XK_space
	{ MODKEY|ShiftMask,             65,  	 togglefloating, {0} },
	//XK_s
	{ MODKEY,                       39,      togglesticky,   {0} },
	//XK_f
        { MODKEY|ShiftMask,             41,      togglefullscr,  {0} },
	//XK_0
	{ MODKEY,                       19,      view,           {.ui = ~0 } },
	//XK_0
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } },
	//XK_comma
	{ MODKEY,                       59,  	 focusmon,       {.i = -1 } },
	//XK_period
	{ MODKEY,                       60, 	 focusmon,       {.i = +1 } },
	//XK_comma
	{ MODKEY|ShiftMask,             59,  	 tagmon,         {.i = -1 } },
	//XK_period
	{ MODKEY|ShiftMask,             60, 	 tagmon,         {.i = +1 } },
	//XK_1
	TAGKEYS(                        10,                      0)
	//XK_2
	TAGKEYS(                        11,                      1)
	//XK_3
	TAGKEYS(                        12,                      2)
	//XK_4
	TAGKEYS(                        13,                      3)
	//XK_5
	TAGKEYS(                        14,                      4)
	//XK_6
	TAGKEYS(                        15,                      5)
	//XK_7
	TAGKEYS(                        16,                      6)
	//XK_8
	TAGKEYS(                        17,                      7)
	//XK_9
	TAGKEYS(                        18,                      8)
	//XK_q
	{ MODKEY|ShiftMask,             24,      quit,           {0} },
	//XK_q
        { MODKEY|ControlMask|ShiftMask, 24,      quit,           {1} },
	//XK_j
	{ MODKEY|ShiftMask,             44,      movestack,      {.i = +1 } },
	//XK_k
	{ MODKEY|ShiftMask,             45,      movestack,      {.i = -1 } },
	//XK_e
	{ MODKEY,                       26,      spawn,          SHCMD("j4-dmenu-desktop --usage-log=$HOME/.cache/desktop-dmenu") },
	//XK_p
	{ MODKEY,                       33,      spawn,          SHCMD("dmenupassmenu") },
	//XK_dead_acute
        { MODKEY,			48,	 spawn,		 {.v = spcalc} },
	//XK_apostrophe
        //{ MODKEY,			48,	 spawn,		 {.v = spcalc} },
	//XK_Return
        { MODKEY|ShiftMask,		36,	 spawn,		 {.v = spterm} },
	//XK_Down
	{ MODKEY,                       116,   	 moveresize,     {.v = "0x 25y 0w 0h" } },
	//XK_j
	{ MODKEY|ControlMask,                       44,   	 moveresize,     {.v = "0x 25y 0w 0h" } },
	//XK_Up
	{ MODKEY,                       111,     moveresize,     {.v = "0x -25y 0w 0h" } },
	//XK_k
	{ MODKEY|ControlMask,                       45,     moveresize,     {.v = "0x -25y 0w 0h" } },
	//XK_Right
	{ MODKEY,                       114,  	 moveresize,     {.v = "25x 0y 0w 0h" } },
	//XK_l
	{ MODKEY|ControlMask,                       46,  	 moveresize,     {.v = "25x 0y 0w 0h" } },
	//XK_Left
	{ MODKEY,                       113,   	 moveresize,     {.v = "-25x 0y 0w 0h" } },
	//XK_h
	{ MODKEY|ControlMask,                       43,   	 moveresize,     {.v = "-25x 0y 0w 0h" } },
	//XK_Down
	{ MODKEY|ShiftMask,             116,   	 moveresize,     {.v = "0x 0y 0w 25h" } },
	//XK_j
	{ MODKEY|ShiftMask|ControlMask,             44,   	 moveresize,     {.v = "0x 0y 0w 25h" } },
	//XK_Up
	{ MODKEY|ShiftMask,             111,     moveresize,     {.v = "0x 0y 0w -25h" } },
	//XK_k
	{ MODKEY|ShiftMask|ControlMask,             45,     moveresize,     {.v = "0x 0y 0w -25h" } },
	//XK_Right
	{ MODKEY|ShiftMask,             114,  	 moveresize,     {.v = "0x 0y 25w 0h" } },
	//XK_l
	{ MODKEY|ShiftMask|ControlMask,             46,  	 moveresize,     {.v = "0x 0y 25w 0h" } },
	//XK_Left
	{ MODKEY|ShiftMask,             113,   	 moveresize,     {.v = "0x 0y -25w 0h" } },
	//XK_h
	{ MODKEY|ShiftMask|ControlMask,             43,   	 moveresize,     {.v = "0x 0y -25w 0h" } },
	//XK_g
        { MODKEY,                       42,      center,         {0} },
	//XK_End
        { MODKEY,                       115,     spawn,     	 SHCMD("sysact") },
	//XK_l
        { MODKEY|ShiftMask,             46,      spawn,     	 SHCMD("kbselect") },

	//XK_Print
	{ 0, 				107,	 spawn,		 SHCMD("maimpick") },
	//{ 0, XF86XK_AudioMute,		spawn,		SHCMD("amixer -q sset Master toggle; pkill -RTMIN+2 dwmblocks") },
	{ 0, 				121,	 spawn,		 SHCMD("pamixer -t; pkill -RTMIN+2 dwmblocks") },
	//{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer -q sset Master 1%+; pkill -RTMIN+2 dwmblocks") },
	{ 0, 				123,	 spawn,		 SHCMD("pamixer --allow-boost -i 1; pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask, 			123,	 spawn,		 SHCMD("light -A 1; pkill -RTMIN+6 dwmblocks") },
	//{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer -q sset Master 1%-; pkill -RTMIN+2 dwmblocks") },
	{ 0, 				122,	 spawn,		 SHCMD("pamixer --allow-boost -d 1; pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask, 			122,	 spawn,		 SHCMD("light -U 1; pkill -RTMIN+6 dwmblocks") },
	//{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	//{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	//{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	//XF86AudioMicMute
	{ 0, 				198,	 spawn,		 SHCMD("amixer -q sset Capture toggle; pkill -RTMIN+13 dwmblocks") },
	//XF86XK_MonBrightnessUp
	//{ 0, 				133,	 spawn,		 SHCMD("light -A 1; pkill -RTMIN+6 dwmblocks") },
	{ 0, 				233,	 spawn,		 SHCMD("light -A 1; pkill -RTMIN+6 dwmblocks") },
	//XF86XK_MonBrightnessDown
	//{ 0, 				132,	 spawn,		 SHCMD("light -U 1; pkill -RTMIN+6 dwmblocks") },
	{ 0, 				232,	 spawn,		 SHCMD("light -U 1; pkill -RTMIN+6 dwmblocks") },
	//XK_space
        { ControlMask, 			65,      spawn,          SHCMD("dunstctl close") },
	//XK_grave
        { ControlMask, 			49,      spawn,          SHCMD("dunstctl history-pop") },
	//XK_space
	{ ControlMask|ShiftMask,	65,      spawn,          SHCMD("[ $(dunstctl is-paused) = true ] && killall -SIGUSR2 dunst || killall -SIGUSR1 dunst; pkill -RTMIN+16 dwmblocks") },
};

#define STATUSBAR "dwmblocks"

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
#ifndef __OpenBSD__
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabFloat,          0,              Button1,        togglefloating, {0} },
    { ClkTabSticky,         0,              Button1,        togglesticky,   {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};

