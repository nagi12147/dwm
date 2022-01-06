/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const int gappx          = 4;        /* gaps between windows */
static unsigned int borderpx    = 2;        /* border pixel of windows */
static unsigned int snap        = 32;       /* snap pixel */
static int showbar              = 1;        /* 0 means no bar */
static int topbar               = 1;        /* 0 means bottom bar */
static const char *fonts[]      = { "monospace:style=bold:pixelsize=15:antialias=true", "Noto Sans Mono CJK JP:style=bold:pixelsize=14:antialias=true" };
static char dmenufont[]         = "monospace:style=bold:pixelsize=15:antialias=true";
static char normfgcolor[]       = "#d0d0d0";
static char normbgcolor[]       = "#151515";
static char normbordercolor[]   = "#151515";
static char selfgcolor[]        = "#d0d0d0";
static char selbordercolor[]    = "#005577";
static char selbgcolor[]        = "#373b41";
static char *colors[][3]        = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title     tags mask   isfloating  monitor */
	{ "Gimp",       NULL,     NULL,     0,          1,          -1 },
	{ TERMCLASS,    NULL,     NULL,     0,          0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color15",    STRING,	    &normfgcolor },
		{ "color0",     STRING,     &normbgcolor },
		{ "color0",     STRING,     &normbordercolor },
		{ "color15",    STRING,     &selfgcolor },
		{ "selbgcolor", STRING,	    &selbgcolor },
		{ "color13",    STRING,	    &selbordercolor },
};

static Key keys[] = {
	/* modifier             key             function            argument */
	TAGKEYS(                XK_1,                               0)
	TAGKEYS(                XK_2,                               1)
	TAGKEYS(                XK_3,                               2)
	TAGKEYS(                XK_4,                               3)
	TAGKEYS(                XK_5,                               4)
	TAGKEYS(                XK_6,                               5)
	TAGKEYS(                XK_7,                               6)
	TAGKEYS(                XK_8,                               7)
	TAGKEYS(                XK_9,                               8)
	{ MODKEY,               XK_d,           spawn,              {.v = dmenucmd } },
	{ MODKEY,               XK_Return,      spawn,              {.v = termcmd } },
	{ MODKEY,               XK_b,           togglebar,          {0} },
	{ MODKEY,               XK_j,           focusstack,         {.i = +1 } },
	{ MODKEY,               XK_k,           focusstack,         {.i = -1 } },
	{ MODKEY,               XK_h,           setmfact,           {.f = -0.05} },
	{ MODKEY,               XK_l,           setmfact,           {.f = +0.05} },
	{ MODKEY,               XK_o,           incnmaster,         {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_o,           incnmaster,         {.i = -1 } },
	{ MODKEY,               XK_space,       zoom,               {0} },
	{ MODKEY|ShiftMask,     XK_space,       togglefloating,     {0} },
	{ MODKEY,               XK_Tab,         view,               {0} },
	{ MODKEY,               XK_q,           killclient,         {0} },
	{ MODKEY,               XK_t,           setlayout,          {.v = &layouts[0]} },
	{ MODKEY,               XK_y,           setlayout,          {.v = &layouts[1]} },
	{ MODKEY,               XK_u,           setlayout,          {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,     XK_f,           fullscreen,         {0} },
	{ MODKEY,               XK_0,           view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,           tag,                {.ui = ~0 } },
	{ MODKEY,               XK_Left,        focusmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Left,        tagmon,             {.i = -1 } },
	{ MODKEY,               XK_Right,       focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Right,       tagmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_q,           spawn,              SHCMD("sysact") },
/*	{ MODKEY|ShiftMask,     XK_q,           quit,               {0} }, */
    { MODKEY,               XK_m,           spawn,              SHCMD("pamixer -t") },
    { MODKEY,               XK_minus,       spawn,              SHCMD("pamixer --allow-boost -d 5") },
    { MODKEY|ShiftMask,     XK_minus,       spawn,              SHCMD("pamixer --allow-boost -d 15") },
    { MODKEY,               XK_equal,       spawn,              SHCMD("pamixer --allow-boost -i 5") },
    { MODKEY|ShiftMask,     XK_equal,       spawn,              SHCMD("pamixer --allow-boost -i 15") },
	{ MODKEY,               XK_w,		    spawn,	        	SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,		    spawn,		        SHCMD("killall $BROWSER") },
	{ MODKEY,		    	XK_r,           spawn,		        SHCMD(TERMINAL " -e lf") },
	{ MODKEY|ShiftMask,		XK_r,           spawn,		        SHCMD(TERMINAL " -e htop") },
	{ MODKEY,		    	XK_e,           spawn,		        SHCMD("dmenuunicode") },
	{ MODKEY,		    	XK_n,           spawn,		        SHCMD("notflix") },
	{ MODKEY|ShiftMask,    	XK_n,           spawn,		        SHCMD(TERMINAL " -e nmtui") },
	{ MODKEY,		    	XK_a,           spawn,		        SHCMD("anki") },
    { MODKEY,               XK_F1,          spawn,              SHCMD("maimpick") },

	#include <X11/XF86keysym.h>
	{ 0, XF86XK_AudioMute,          spawn,      SHCMD("pamixer -t")  },
	{ 0, XF86XK_AudioLowerVolume,   spawn,      SHCMD("pamixer --allow-boost -d 5") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pamixer --allow-boost -i 5") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

