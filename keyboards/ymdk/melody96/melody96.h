#pragma once

#include "quantum.h"

#define XXX KC_NO

/*
 * ┌────┬───┐                                          ┌───┬───┐
 * │10  │11 │                                          │A3 │A6 │
 * └────┴───┘                                          └───┴───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │50 │51 │52 │53 │54 │55 │56 │57 │58 │B8 │B7 │B5 │B4 │B3 │B6 │B2 │B1 │B0 │63 │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┼───┼───┼───┤
 * │40 │41 │42 │43 │44 │45 │46 │47 │48 │A8 │A7 │A5 │A4 │A6     │A2 │A1 │A0 │64 │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┼───┼───┼───┤    ┌─────┐ ┌───┐
 * │30   │31 │32 │33 │34 │35 │36 │37 │38 │98 │97 │95 │94 │93   │96 │92 │91 │80 │    │93   │ │90 │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┼───┼───┤   │ ┌──┴┐    │ ├───┤
 * │20    │21 │22 │23 │24 │25 │26 │27 │28 │88 │87 │85 │84      │86 │82 │81 │   │ │84 │    │ │80 │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┼───┼───┼───┤ ├───┼────┘ └───┘
 * │10      │12 │13 │14 │15 │16 │17 │18 │78 │77 │75 │74    │73 │76 │72 │71 │60 │ │70 │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┴───┼───┤   │ ├───┤
 * │00  │01  │02  │06                      │08 │07 │05 │04 │03 │62     │61 │   │ │60 │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───────┴───┴───┘ └───┘
 *                                                  ┌──────────┬───┬───┐
 *                                                  │74        │66 │62 │
 *                                                  └──────────┴───┴───┘
 * ┌────┬────┬────┬────────────────────────┬─────┬─────┬───┬───┐
 * │00  │01  │02  │06                      │08   │05   │04 │03 │
 * └────┴────┴────┴────────────────────────┴─────┴─────┴───┴───┘
 * ┌────┬────┬────┬─────────────────────────────┬────┬────┬────┐
 * │00  │01  │02  │06                      │08  │07  │04  │03  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 * ┌─────┬─────┬───────────────────────────┬─────┬─────┬───┬───┐
 * │00   │01   │06                         │08   │05   │04 │03 │
 * └─────┴─────┴───────────────────────────┴─────┴─────┴───┴───┘
 * ┌─────┬─────┬───────────────────────────┬────┬────┬────┬────┐
 * │00   │01   │06                         │08  │07  │04  │03  │
 * └─────┴─────┴───────────────────────────┴────┴────┴────┴────┘
 * ┌─────┬─────┬───────────────────────────┬───┬───┬───┬───┬───┐
 * │00   │01   │06                         │08 │07 │05 │04 │03 │
 * └─────┴─────┴───────────────────────────┴───┴───┴───┴───┴───┘
 * ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 * │00   │01 │02   │06                         │07   │04 │03   │
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 * ┌─────┬───┬─────┬───────────────────────────┬───┬───┬───┬───┐
 * │00   │01 │02   │06                         │07 │05 │04 │03 │
 * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
 * ┌─────┬───┬─────┬───────────────────────┬─────┬─────┬───┬───┐
 * │00   │01 │02   │06                     │08   │05   │04 │03 │
 * └─────┴───┴─────┴───────────────────────┴─────┴─────┴───┴───┘
 * ┌─────┬───┬─────┬───────────────────────┬───┬───┬───┬───┬───┐
 * │00   │01 │02   │06                     │08 │07 │05 │04 │03 │
 * └─────┴───┴─────┴───────────────────────┴───┴───┴───┴───┴───┘
 * ┌─────┬───┬─────┬───────────────────────┬────┬────┬────┬────┐
 * │00   │01 │02   │06                     │08  │07  │04  │03  │
 * └─────┴───┴─────┴───────────────────────┴────┴────┴────┴────┘
 */

#define LAYOUT_all( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA3, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k93, k96, k92, k91, k90, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k84, k86, k82, k81, k80, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k78, k77, k75, k74, k73, k76, k72, k71, k70, \
    k00, k01, k02,                k06,           k08, k07, k05, k04, k03, k66, k62, k61, k60 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_ansi( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k93, k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k84, k86, k82, k81, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k78, k77, k75, k74, k73, k76, k72, k71, k60, \
    k00, k01, k02,                k06,           k08, k07, k05, k04, k03, k66, k62, k61 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, XXX, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_ansi_splitbs( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA3, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k93, k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k84, k86, k82, k81, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k78, k77, k75, k74, k73, k76, k72, k71, k60, \
    k00, k01, k02,                k06,           k08, k07, k05, k04, k03, k66, k62, k61 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, XXX, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_iso( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94,      k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85, k84, k93, k86, k82, k81, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k78, k77, k75, k74, k73, k76, k72, k71, k60, \
    k00, k01, k02,                k06,           k08, k07, k05, k04, k03, k66, k62, k61 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, XXX, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_iso_splitbs( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA3, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94,      k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85, k84, k93, k86, k82, k81, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k78, k77, k75, k74, k73, k76, k72, k71, k60, \
    k00, k01, k02,                k06,           k08, k07, k05, k04, k03, k66, k62, k61 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_with60( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k84, k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k93, k86, k82, k81, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k78, k77, k75,      k74, k76, k72, k71, k60,\
    k00, k01, k02,                k06,                k08, k07, k04, k03, k62,      k61 \
) { \
    { k00, k01, k02, k03, k04, XXX, k06, k07, k08 }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, XXX, XXX, XXX }, \
    { XXX, k71, k72, XXX, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, XXX, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_with60_splitbs( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA3, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k84, k96, k92, k91, k80, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k93, k86, k82, k81, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k78, k77, k75,      k74, k76, k72, k71, k60, \
    k00, k01, k02,                k06,                k08, k07, k04, k03, k62,      k61 \
) { \
    { k00, k01, k02, k03, k04, XXX, k06, k07, k08 }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, XXX, XXX, XXX }, \
    { XXX, k71, k72, XXX, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}

#define LAYOUT_96_with60_split_num0( \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, kB8, kB7, kB5, kB4, kB3, kB6, kB2, kB1, kB0, k63, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, kA8, kA7, kA5, kA4, kA6, kA2, kA1, kA0, k64, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k98, k97, k95, k94, k84, k96, k92, k91, k80,\
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85,      k93, k86, k82, k81, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k78, k77, k75,      k74, k76, k72, k71, k60, \
    k00, k01, k02,                k06,                k08, k07, k04, k03, k66, k62, k61 \
) { \
    { k00, k01, k02, k03, k04, XXX, k06, k07, k08 }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, XXX, k66, XXX, XXX }, \
    { XXX, k71, k72, XXX, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, XXX, k84, k85, k86, k87, k88 }, \
    { XXX, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { kA0, kA1, kA2, XXX, kA4, kA5, kA6, kA7, kA8 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8 } \
}