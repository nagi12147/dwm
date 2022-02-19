/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:style=bold:pixelsize=15", "Noto Color Emoji:pixelsize=12", "Symbols Nerd Font:pixelsize=16" };
static const char dmenufont[]       = "monospace:style=bold:pixelsize=15";
static const char bg0_h[]           = "#1d2021";
static const char bg[]              = "#282828";
static const char bg1[]             = "#3c3836";
static const char fg4[]             = "#a89984";
static const char fg[]              = "#ebdbb2";
static const char warna[]           = "#b16286";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg4, bg0_h, bg },
	[SchemeSel]  = { fg, bg1,  warna  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bg0_h, "-nf", fg4, "-sb", bg1, "-sf", fg, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
    //{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_f,      fullscreen,     {0} },
    { MODKEY,                       XK_z,      incrgaps,       {.i = +1 } },
    { MODKEY,                       XK_x,      incrgaps,       {.i = -1 } },
    { MODKEY,                       XK_a,      togglegaps,     {0} },
    { MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
    { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_minus,  spawn,          SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,             XK_minus,  spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_equal,  spawn,          SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,             XK_equal,  spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },

    { 0,                            XK_Print,  spawn,          SHCMD("maimfull") },
    { MODKEY,                       XK_F1,     spawn,          SHCMD("maimselc") },
    { MODKEY,                       XK_F2,     spawn,          SHCMD("maimwinc") },
    { MODKEY,                       XK_F3,     spawn,          SHCMD("maimfullc") },
    { MODKEY|ShiftMask,             XK_F1,     spawn,          SHCMD("maimsel") },
    { MODKEY|ShiftMask,             XK_F2,     spawn,          SHCMD("maimwin") },
    { MODKEY|ShiftMask,             XK_F3,     spawn,          SHCMD("maimfull") },
    { MODKEY,                       XK_F12,    spawn,          SHCMD("dmount") },
    { MODKEY|ShiftMask,             XK_F12,    spawn,          SHCMD("dunmount") },
    { MODKEY,                       XK_e,      spawn,          SHCMD("emoji") },
    { MODKEY,                       XK_n,      spawn,          SHCMD("notflix") },
    { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD(TERMINAL " -e sudo nmtui") },
    { MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e lf") },
    { MODKEY,                       XK_v,      spawn,          SHCMD(TERMINAL " -e nvim $HOME/doc/Note.md") },
    { MODKEY|ShiftMask,             XK_y,      spawn,          SHCMD(TERMINAL " -e ytfzf -t") },
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("chromium") },

    { 0, XF86XK_AudioMute,          spawn,                     SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,   spawn,                     SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,                     SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_MonBrightnessUp,    spawn,                     SHCMD("xbacklight -inc 10") },
    { 0, XF86XK_MonBrightnessDown,  spawn,                     SHCMD("xbacklight -dec 10") },
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

