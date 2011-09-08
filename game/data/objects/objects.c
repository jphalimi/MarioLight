//
//  objects.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "../../object/object.h"
#include "../../object/object_state.h"
#include "states_handlers.h"
#include "objects.h"

/* EMPTY for the moment ;) */

SObject *InterrogationPoint_create (void) {
    //Object_create(<#const char *name#>, <#unsigned int nb_sprites#>, <#const char *sprites_folder#>,<#uint32_t sprite_duration#>, <#float max_speed#>, <#float acceleration#>, <#float speed#>X, <#float speed#>Y)
    SObject *object = Object_create("InterrogationPoint", 9, "game/images/interrogation_point", 130, 4.27, 0.3, 0.0, 0.0);
    
    /* Standing handling */
    {
        unsigned scheme[] = {0,1,2,3,4,5};
        Object_setScheme (object, OBJECT_ISSTANDING, scheme, sizeof(scheme) / sizeof(*scheme));
        Object_setUpdateSpriteHandler(object, OBJECT_ISSTANDING, OS_interrogationStandingSprite);
    }
    Object_setCurrentState(object, OBJECT_ISSTANDING);
    Object_setX(object, 300);
    Object_setY(object, 50);
    
    return object;
}

SObject *Canon_create (void) {
    //Object_create(<#const char *name#>, <#unsigned int nb_sprites#>, <#const char *sprites_folder#>,<#uint32_t sprite_duration#>, <#float max_speed#>, <#float acceleration#>, <#float speed#>X, <#float speed#>Y)
    SObject *object = Object_create("Canon", 1, "game/images/canon", 130, 4.27, 0.3, 0.0, 0.0);
    
    /* Standing handling */
    {
        unsigned scheme[] = {0};
        Object_setScheme (object, OBJECT_ISSTANDING, scheme, sizeof(scheme) / sizeof(*scheme));
        Object_setUpdateSpriteHandler(object, OBJECT_ISSTANDING, NULL);
    }
    Object_setCurrentState(object, OBJECT_ISSTANDING);
    Object_setX(object, 150);
    Object_setY(object, 0);
    
    return object;
}