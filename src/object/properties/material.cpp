#include "material.h"
#include "../../utils/ExData.h"

void Material::setMaterial(Material::materials m) {
	switch (m)
	{
	case Material::emerald:
		assginMaterialData(ExData::getMaterialsData("emerald"));
		break;
	case Material::jade:
		assginMaterialData(ExData::getMaterialsData("jade"));
		break;
	case Material::obsidian:
		assginMaterialData(ExData::getMaterialsData("obsidian"));
		break;
	case Material::pearl:
		assginMaterialData(ExData::getMaterialsData("pearl"));
		break;
	case Material::ruby:
		assginMaterialData(ExData::getMaterialsData("ruby"));
		break;
	case Material::turquoise:
		assginMaterialData(ExData::getMaterialsData("turquoise"));
		break;
	case Material::brass:
		assginMaterialData(ExData::getMaterialsData("brass"));
		break;
	case Material::bronze:
		assginMaterialData(ExData::getMaterialsData("bronze"));
		break;
	case Material::chrome:
		assginMaterialData(ExData::getMaterialsData("chrome"));
		break;
	case Material::copper:
		assginMaterialData(ExData::getMaterialsData("copper"));
		break;
	case Material::gold:
		assginMaterialData(ExData::getMaterialsData("gold"));
		break;
	case Material::silver:
		assginMaterialData(ExData::getMaterialsData("silver"));
		break;
	case Material::black_plastic:
		assginMaterialData(ExData::getMaterialsData("black_plastic"));
		break;
	case Material::cyan_plastic:
		assginMaterialData(ExData::getMaterialsData("cyan_plastic"));
		break;
	case Material::green_plastic:
		assginMaterialData(ExData::getMaterialsData("green_plastic"));
		break;
	case Material::red_plastic:
		assginMaterialData(ExData::getMaterialsData("red_plastic"));
		break;
	case Material::white_plastic:
		assginMaterialData(ExData::getMaterialsData("white_plastic"));
		break;
	case Material::yellow_plastic:
		assginMaterialData(ExData::getMaterialsData("yellow_plastic"));
		break;
	case Material::black_rubber:
		assginMaterialData(ExData::getMaterialsData("black_rubber"));
		break;
	case Material::cyan_rubber:
		assginMaterialData(ExData::getMaterialsData("cyan_rubber"));
		break;
	case Material::green_rubber:
		assginMaterialData(ExData::getMaterialsData("green_rubber"));
		break;
	case Material::red_rubber:
		assginMaterialData(ExData::getMaterialsData("red_rubber"));
		break;
	case Material::white_rubber:
		assginMaterialData(ExData::getMaterialsData("white_rubber"));
		break;
	case Material::yellow_rubber:
		assginMaterialData(ExData::getMaterialsData("yellow_rubber"));
		break;
	default:
		//TODO:LOG ERROR
		break;
	}
}


void Material::assginMaterialData(const std::vector<float> &data) {
	if (data.size() != 10) {
		//TODO:LOG ERROR
		return;
	}

	ambient.x = data[0];
	ambient.y = data[1];
	ambient.z = data[2];

	diffuse.x = data[3];
	diffuse.y = data[4];
	diffuse.z = data[5];

	specular.x = data[6];
	specular.y = data[7];
	specular.z = data[8];

	shininess = data[9];
}