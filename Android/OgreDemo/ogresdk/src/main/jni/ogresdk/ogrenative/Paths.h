#ifndef OGRE_PATHS_H
#define OGRE_PATHS_H

namespace OgreNative
{
	class Paths
	{
	public:
		~Paths();

		unsigned int Size();
		const char* operator[] ( unsigned int uiIndex ) const;

	private:
		unsigned int m_uiSize;
		char** m_pPaths;

		Paths( char** pPaths, unsigned int uiSize );

		friend class AssetManager;
	};

}

#endif
