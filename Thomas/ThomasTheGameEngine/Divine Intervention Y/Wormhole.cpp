#include "Wormhole.h"

#include "DIY_Level.h"

Wormhole::Wormhole(Level * level_, Vec3 position_, int layerIndex) : GameObject(level_, position_)
{
	destinationLayer = layerIndex;

	rc = new RenderableComponent("cuboid", "planet1", this);
}

Layer * Wormhole::getDestinationLayer()
{
	DIY_Level * gl = static_cast<DIY_Level *>(level);

	return gl->layers[destinationLayer];
}

//void Wormhole::setDestinationLayer(Layer * layer_)
//{
//	destinationLayer = layer_;
//}