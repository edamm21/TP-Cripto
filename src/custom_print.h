//
// Created by Nacho Grasso on 20/06/2021.
//

#ifndef TP_CRIPTO_CUSTOM_PRINT_H
#define TP_CRIPTO_CUSTOM_PRINT_H

#define NONE        "\e[0m"
#define  L_GREEN    "\e[1;32m"
#define L_CYAN      "\e[1;36m"
#define BOLD        "\e[1m"
#define UNDERLINE   "\e[4m"

#define printlnu(format, arg...) do{printf(NONE  format NONE,## arg);}while(0)
#define printlnb(format, arg...) do{printf(BOLD  format NONE,## arg);}while(0)
#define printlcn(format, arg...) do{printf(L_CYAN  format NONE,## arg);}while(0)
#define printlgu(format, arg...) do{printf(L_GREEN UNDERLINE format NONE,## arg);}while(0)

#endif //TP_CRIPTO_CUSTOM_PRINT_H
