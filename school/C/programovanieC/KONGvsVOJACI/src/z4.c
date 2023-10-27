#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "rng.h"
#include "data.h"


// TODO: miesto pre pripojenie externej funkcionality z ostatnych
//  suborov projektu.

// TODO: miesto pre implementaciu vasich vlastnych funkcii, datovych
//  typov a vlastne makra.
int DMG(Unit attacker, Unit defender);
void counterAttack(Unit *monster,Unit army[],int number);
int TheWeakest(Unit vojaciky[],int number);
void vypisVojaciky(Unit vojaciky[],int number);
int main(int argc, char *argv[]) {

    char ach[100];
    strcpy(ach, argv[1]);
    int number = atoi(argv[2]);
    int seed = atoi(argv[3]);

    UnitType vojacikynahrada[ENEMY_TYPE_COUNT];

    if (argc == 6) {
    char *filename;

    filename = argv[5];

    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL) {
        return 2;
    }
    char buf[11];

    int m = 0;
    while (fscanf(f, "%s", buf) != EOF) {
            strcpy(vojacikynahrada[m].name, buf);
            if (!((*buf > 40 && *buf < 91) || (*buf > 96 && *buf < 123)))
                return 3;

            fscanf(f, "%s", buf);
            vojacikynahrada[m].att = atoi(buf);
            if (!(*buf > 47 && *buf < 58))
                return 3;

            fscanf(f, "%s", buf);
            vojacikynahrada[m].def = atoi(buf);
            if (!(*buf > 47 && *buf < 58))
                return 3;
            m++;
        }


    }
    srnd(seed);

    UnitType figter;
    Unit monster;
    int ishere=0;

    for (int i = 0; i < 3; ++i) {
        if ((strcmp(monster_types[i].name,ach) == 0) && (strlen(monster_types[i].name) == strlen(ach))){
            ishere = 1;
            figter = monster_types[i];
            monster.type = &figter;
            monster.hp = MONSTER_INITIAL_HP;
            monster.level = 0;
            printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",figter.name,monster.type->att,monster.type->def,monster.hp,monster.level);

        }
    }
    if (ishere != 1)
        return 1;

    UnitType type[number];
    int hp;
    int level;
    Unit vojaciky[number];

    for (int i = 0; i < number; i++) {
        if (argc==4)
            type[i] = enemy_types[rnd(0, ENEMY_TYPE_COUNT - 1)];
        else
            type[i] = vojacikynahrada[rnd(0, ENEMY_TYPE_COUNT - 1)];
        hp = rnd(ENEMY_MIN_INIT_HP, ENEMY_MAX_INIT_HP);
        level = rnd(0, UNIT_MAX_LEVEL);
        vojaciky[i].type = &type[i];
        vojaciky[i].hp = hp;
        vojaciky[i].level = level;
        printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",i,vojaciky[i].type->name, vojaciky[i].type->att,
               vojaciky[i].type->def, vojaciky[i].hp, vojaciky[i].level);
    }

    int dmg ,weak;
    int deadarmy=1;
    int totaldmg=0;
    while(monster.hp > 0 && (deadarmy != 0)) {

        deadarmy = number;
        weak = TheWeakest(vojaciky, number);
        dmg = DMG(monster, vojaciky[weak]);
        totaldmg = totaldmg + dmg;
        printf("\n");
        printf("%s => %d => [%d] %s\n",monster.type->name,dmg,weak,vojaciky[weak].type->name);
        vojaciky[weak].hp -= dmg;
        counterAttack(&monster, vojaciky, number);
        printf("\n");
        printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",figter.name,monster.type->att,monster.type->def,monster.hp,monster.level);
        vypisVojaciky(vojaciky, number);

        for (int j = 0; j < number; ++j) {
            if (vojaciky[j].hp <= 0)
                deadarmy--;
        }


    }

    printf("\n");
    if (monster.hp > 0)
        printf("Winner: %s\n",monster.type->name);
    else
        printf("Winner: Enemy\n");
    printf("Total monster DMG: %d\n",totaldmg);
    printf("Total enemies DMG: %d \n",500-monster.hp);

    return 0;
}

int DMG(Unit attacker, Unit defender){
    int base_dmg,c1,c2,strenght,defense,d1,d2,DMG;
    base_dmg = 30 + attacker.level - defender.level;
    c1 = rnd(1, attacker.hp);
    c2 = attacker.type->att;
    strenght = 100 + c1 + c2;
    d1 = rnd(1,defender.hp);
    d2 = defender.type->def;
    defense = 100 + d1 + d2;
    DMG = (base_dmg * strenght) /defense;
    return DMG;
}
void counterAttack(Unit *monster,Unit army[],int number){

    int dmg;
    for (int i = 0; i < number; i++) {
        if (army[i].hp > 0) {

            dmg = DMG(army[i], *monster);
            printf("[%d] %s => %d => %s\n",i, army[i].type->name,dmg,monster->type->name);

            monster->hp = monster->hp- dmg;
            if (monster->hp < 0 )
                break;


        }
    }
    if (monster->level <10 && monster->hp > 0)
        monster->level++;

}

int TheWeakest(Unit vojaciky[],int number){
    Unit  target = {NULL, 0, 0};
    int cross=1;
    int a =0;
    int b =0;
    int help = 0;
    for (int i = 0; i < number; ++i) {
        if (vojaciky[i].hp > 0 && cross==1) {
            target = vojaciky[i];
            a = i;
            cross = 0;
            help = 1;
        }else
        { if (help==0)
        b++;}
    }

    for (int i = 0; i < number; ++i) {
       // printf("target.%d > vojaciky[0].%d && vojaciky[0].%d > 0 \n",target.hp,vojaciky[i].hp,vojaciky[i].hp);
        if (target.hp > vojaciky[i].hp && vojaciky[i].hp > 0){
            a = i;
            target = vojaciky[i];

        }
    }

    return a;
}

void vypisVojaciky(Unit vojaciky[],int number){
    for (int i = 0; i < number; ++i) {
        printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",i,vojaciky[i].type->name, vojaciky[i].type->att,
               vojaciky[i].type->def, vojaciky[i].hp, vojaciky[i].level);
    }
}
