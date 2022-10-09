/* See LICENSE file for copyright and license details. */

/* appearance */
static char font[]        = "DejaVu Sans:pixelsize=14";
static char* normbgcolor  = "#1f5393";
static char* normfgcolor  = "#cccccc";
static char* selbgcolor   = "#4185d7";
static char* selfgcolor   = "#ffffff";
static char* urgbgcolor   = "#2b2b2b";
static char* urgfgcolor   = "#df2800";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -b -l 5 -r -i -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",         STRING,  &font },
		{ "normbgcolor",  STRING,  &normbgcolor },
		{ "normfgcolor",  STRING,  &normfgcolor },
		{ "selbgcolor",   STRING,  &selbgcolor },
		{ "selfgcolor",   STRING,  &selfgcolor },
		{ "urgbgcolor",   STRING,  &urgbgcolor },
		{ "urgfgcolor",   STRING,  &urgfgcolor },
};

#define MODKEY ControlMask
#define ALTKEY Mod1Mask
static const Key keys[] = {
    /* modifier             key        function     argument */
    { MODKEY,               XK_Return, focusonce,   { 0 } },
    { MODKEY,               XK_Return, spawn,       { 0 } },

    { MODKEY,               XK_l,      rotate,      { .i = +1 } },
    { MODKEY,               XK_Right,  rotate,      { .i = +1 } },
    { MODKEY,               XK_h,      rotate,      { .i = -1 } },
    { MODKEY,               XK_Left,   rotate,      { .i = -1 } },
    { MODKEY,               XK_j,      movetab,     { .i = -1 } },
    { MODKEY,               XK_Up,     movetab,     { .i = -1 } },
    { MODKEY,               XK_k,      movetab,     { .i = +1 } },
    { MODKEY,               XK_Down,   movetab,     { .i = +1 } },
    { MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

    { MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
    { ALTKEY,               XK_1,      move,        { .i = 0 } },
    { ALTKEY,               XK_2,      move,        { .i = 1 } },
    { ALTKEY,               XK_3,      move,        { .i = 2 } },
    { ALTKEY,               XK_4,      move,        { .i = 3 } },
    { ALTKEY,               XK_5,      move,        { .i = 4 } },
    { ALTKEY,               XK_6,      move,        { .i = 5 } },
    { ALTKEY,               XK_7,      move,        { .i = 6 } },
    { ALTKEY,               XK_8,      move,        { .i = 7 } },
    { ALTKEY,               XK_9,      move,        { .i = 8 } },
    { ALTKEY,               XK_0,      move,        { .i = 9 } },

    { ALTKEY,               XK_q,      killclient,  { 0 } },

    { MODKEY,               XK_u,      focusurgent, { 0 } },
    { MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

    { 0,                    XK_F11,    fullscreen,  { 0 } },
};
