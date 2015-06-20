#include "Entity.hpp"

static unsigned int last_id = 0;
Entity::Entity(): id(last_id++) { }
