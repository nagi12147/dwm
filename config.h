/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:style=bold:pixelsize=18", "M PLUS 1 Code:style=bold:size=10", "Noto Color Emoji:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#353535"; /*444444*/
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ TERMCLASS,    NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,         NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
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
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
	/* modifier                     key                         function        argument */
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
	{ MODKEY,                       XK_d,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,                       incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,                   zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
    { MODKEY,                       XK_s,                       togglesticky,   {0} },
	{ MODKEY,                       XK_f,                       fullscreen,     {0} },
	{ MODKEY|ShiftMask,             XK_q,                       spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_m,                       spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+1 dwmblocks") },
 	{ MODKEY,                       XK_equal,                   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+1 dwmblocks") },
 	{ MODKEY|ShiftMask,             XK_equal,                   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +15%; pkill -RTMIN+1 dwmblocks") },
 	{ MODKEY,                       XK_minus,                   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+1 dwmblocks") },
 	{ MODKEY|ShiftMask,             XK_minus,                   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -15%; pkill -RTMIN+1 dwmblocks") },
 	{ MODKEY,                       XK_bracketright,            spawn,          SHCMD("xbacklight -inc 5") },
 	{ MODKEY|ShiftMask,             XK_bracketright,            spawn,          SHCMD("xbacklight -inc 5") },
 	{ MODKEY,                       XK_bracketleft,             spawn,          SHCMD("xbacklight -dec 5") },
 	{ MODKEY|ShiftMask,             XK_bracketleft,             spawn,          SHCMD("xbacklight -dec 10") },
   	{ 0,                            XK_Print,                   spawn,          SHCMD("maim-full") },
   	{ MODKEY,                       XK_F1,                      spawn,          SHCMD("maim-selc") },
   	{ MODKEY,                       XK_F2,                      spawn,          SHCMD("maim-winc") },
   	{ MODKEY,                       XK_F3,                      spawn,          SHCMD("maim-fullc") },
   	{ MODKEY|ShiftMask,             XK_F1,                      spawn,          SHCMD("maim-sel") },
   	{ MODKEY|ShiftMask,             XK_F2,                      spawn,          SHCMD("maim-win") },
   	{ MODKEY|ShiftMask,             XK_F3,                      spawn,          SHCMD("maim-full") },
   	{ MODKEY,                       XK_F4,                      spawn,          SHCMD("dmenu-monitor") },
   	{ MODKEY,                       XK_F12,                     spawn,          SHCMD("dmenu-mount") },
   	{ MODKEY|ShiftMask,             XK_F12,                     spawn,          SHCMD("dmenu-umount") },
   	{ MODKEY,                       XK_e,                       spawn,          SHCMD("emoji") },
   	{ MODKEY,                       XK_r,                       spawn,          SHCMD(TERMINAL " -e lf") },
   	{ MODKEY,                       XK_v,                       spawn,          SHCMD(TERMINAL " -e nvim $HOME/docs/Note.md") },
   	{ MODKEY|ShiftMask,             XK_w,                       spawn,          SHCMD("word-lookup") },
   	{ MODKEY,                       XK_n,                       spawn,          SHCMD(TERMINAL " -e iwctl") },
   	{ MODKEY,                       XK_p,                       spawn,          SHCMD("yt-play") },
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

