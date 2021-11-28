/* See LICENSE file for copyright and license details. */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Terminus", "Noto Color Emoji", "fontawesome" };
static const char dmenufont[]       = "Terminus";

/*
static const char col_gray1[]       =  "#111111";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#990096";  // "#c4037a"; 
static const char urgbordercolor[]  = "#ff0000";


static const char *colors[][3]      = {
	//               fg         bg         border   
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
*/

//COLOR-CONFIG-START
static const char norm_fg[] = "#f5aa78";
static const char norm_bg[] = "#050A0E";
static const char norm_border[] = "#ab7654";

static const char sel_fg[] = "#f5aa78";
static const char sel_bg[] = "#FD0E01";
static const char sel_border[] = "#f5aa78";

static const char urg_fg[] = "#f5aa78";
static const char urg_bg[] = "#A03D10";
static const char urg_border[] = "#A03D10";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
//COLOR-CONFIG-END


/* tagging */
static const char *tags[] = { " ", " ", " ", " ", " ", " ", " ", " ", " " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  		NULL,       NULL,       1 << 8,       0,           -1 },
	{ "mpv",      		NULL,       NULL,       1 << 5,       0,           -1 },
	{ "librewolf",		NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Signal",     	NULL,       NULL,       1 << 2,       0,           -1 },
	{ "firefox",		NULL,       NULL,       1 << 2,       0,           -1 },
	{ "discord",      	NULL,       NULL,       1 << 2,       0,           -1 },
	{ "obs",      		NULL,       NULL,       1 << 7,       0,           -1 },
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
};

/* key definitions */
#define MODKEY Mod4Mask
#define LAUNCHKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run","-h", "20", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg , "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/* My scripts */
static const char *pipecatcmd[] = { "pipecat-turbo", NULL };
static const char *killercmd[] = { "/home/wojnstup/Media/killer.sh", NULL };
static const char *searchtermcmd[] = { "alacritty", "-e", "/home/wojnstup/Media/ddg.sh", NULL };
static const char *pirokitcmd[] = { "/home/wojnstup/Media/pirokit", NULL };
static const char *anicmd[] = { "alacritty", "-e", "ani-cli", "-H", NULL };
static const char *muscmd[] = { "alacritty", "-e", "/home/wojnstup/Media/pipecat.sh", NULL };

/* Apps */
static const char *elementcmd[] = { "surf","https://app.element.io/?pk_vid=8c5f5180c181a9601636221127319abc", NULL };
static const char *browsercmd[] = { "librewolf", NULL };

/* Volume commands */
static const char *vollowcmd[] = { "amixer", "-c", "0", "set", "Master", "5%-", NULL };
static const char *volhighcmd[] = { "amixer", "-c", "0", "set", "Master", "5%+", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY, 	            	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} }, 
	{ MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_p,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[2]} },
//	GAPS
	{ MODKEY,                       XK_q,  	   setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_w,      setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_e,      setgaps,        {.i = 0  } },
//	Custom keybindings
	{ LAUNCHKEY,			XK_l,	   spawn, 	   {.v = pipecatcmd } },
	{ LAUNCHKEY,                    XK_k,      spawn,          {.v = killercmd } },
	{ LAUNCHKEY,                    XK_f,      spawn,          {.v = browsercmd } },
	{ LAUNCHKEY,                    XK_e,      spawn,          {.v = elementcmd } },
	{ LAUNCHKEY,                    XK_z,      spawn,          {.v = searchtermcmd } },
	{ LAUNCHKEY,                    XK_a,      spawn,          {.v = anicmd } },
	{ LAUNCHKEY,                    XK_t,      spawn,          {.v = pirokitcmd } },
	{ LAUNCHKEY,                    XK_m,      spawn,          {.v = muscmd } },

//	Volume
	{ MODKEY,                    	XK_minus,  spawn,          {.v = vollowcmd } },
	{ MODKEY,                    	XK_equal,  spawn,          {.v = volhighcmd } },

//	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,		        XK_t,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
