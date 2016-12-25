#pragma once 

#ifdef RTSHADER_SYSTEM_BUILD_CORE_SHADERS

#include "Ogre.h"
#include "OgreRTShaderSystem.h"

namespace Ogre
{
class ShaderGeneratorTechniqueResolverListener : public MaterialManager::Listener
{
public:

    ShaderGeneratorTechniqueResolverListener(RTShader::ShaderGenerator* pShaderGenerator)
    {
        mShaderGenerator = pShaderGenerator;
    }

    virtual Technique* handleSchemeNotFound(unsigned short schemeIndex,
        const String& schemeName, Material* originalMaterial, unsigned short lodIndex,
        const Renderable* rend)
    {
        // Case this is the default shader generator scheme.
        if (schemeName == RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
        {
            MaterialRegisterIterator itFind = mRegisteredMaterials.find(originalMaterial);
            bool techniqueCreated = false;

            // This material was not registered before.
            if (itFind == mRegisteredMaterials.end())
            {
                techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
                    originalMaterial->getName(),
                    MaterialManager::DEFAULT_SCHEME_NAME,
                    schemeName);
            }
            mRegisteredMaterials[originalMaterial] = techniqueCreated;
        }

        return NULL;
    }

protected:
    typedef std::map<Material*, bool>        MaterialRegisterMap;
    typedef MaterialRegisterMap::iterator    MaterialRegisterIterator;


protected:
    MaterialRegisterMap                mRegisteredMaterials;        // Registered material map.
    RTShader::ShaderGenerator*        mShaderGenerator;            // The shader generator instance.
};
}
#endif
