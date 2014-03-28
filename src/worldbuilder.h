/*
 * worldbuilder.h
 *
 *  Created on: March 25, 2014
 *      Author: Bjorn Blissing
 */
#ifndef _WORLDBUILDER_H_
#define _WORLDBUILDER_H_

#include "buildinglibrary.h"
#include "texturelibrary.h"
#include "heighttile.h"
#include "shapetile.h"

class WorldBuilder : public osg::Referenced {
public:
	WorldBuilder(std::string configFilename, std::string outputFilename=std::string("")) : m_configFilename(configFilename),
	m_outputFilename(outputFilename) {};
	void loadConfiguration();
	void buildWorld();
protected:
	~WorldBuilder() {}

	void addPolygonsToHeight(PolygonVector polygons);
	
	std::string m_configFilename;
	std::string m_outputFilename;

	std::vector<std::string> m_shapeFilenames;
	std::vector<std::string> m_heigthFilenames;

	HeightTileVector m_heightTiles;
	ShapeWorldVector m_shapeTiles;
	PolygonVector m_polygonsOutsideTiles;
};

#endif
