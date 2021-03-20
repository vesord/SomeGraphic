#ifndef MATERIALS_H
#define MATERIALS_H

typedef enum e_material_type {
	MATERIAL_NONE,
	MATERIAL_GOLD,
	MATERIAL_SILVER,
	MATERIAL_POLISHED_BRONZE,
	MATERIAL_TURQUOISE,
	MATERIAL_PERL,
	MATERIAL_END
}			 t_material_type;

void applyMaterial(GLenum cullMode, t_material_type materialType);

#endif //MATERIALS_H
