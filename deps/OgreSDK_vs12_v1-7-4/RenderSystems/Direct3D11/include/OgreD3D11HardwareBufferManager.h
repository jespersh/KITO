/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __D3D11HARWAREBUFFERMANAGER_H__
#define __D3D11HARWAREBUFFERMANAGER_H__

#include "OgreD3D11Prerequisites.h"
#include "OgreHardwareBufferManager.h"

namespace Ogre {

	/** Implementation of HardwareBufferManager for D3D11. */
	class D3D11HardwareBufferManagerBase : public HardwareBufferManagerBase
	{
	protected:
		D3D11Device & mlpD3DDevice;

		/// Internal method for creates a new vertex declaration, may be overridden by certain rendering APIs
		VertexDeclaration* createVertexDeclarationImpl(void);
		/// Internal method for destroys a vertex declaration, may be overridden by certain rendering APIs
		void destroyVertexDeclarationImpl(VertexDeclaration* decl);

	public:
		D3D11HardwareBufferManagerBase(D3D11Device & device);
		~D3D11HardwareBufferManagerBase();
		/// Creates a vertex buffer
		HardwareVertexBufferSharedPtr 
			createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
		/// Create a hardware vertex buffer
		HardwareIndexBufferSharedPtr 
			createIndexBuffer(HardwareIndexBuffer::IndexType itype, size_t numIndexes, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
		/// @copydoc HardwareBufferManager::createRenderToVertexBuffer
		RenderToVertexBufferSharedPtr createRenderToVertexBuffer();

		/** Release all buffers in the default memory pool. 
		@remarks
		Method for dealing with lost devices.
		*/
		void releaseDefaultPoolResources(void);
		/** Recreate all buffers in the default memory pool. 
		@remarks
		Method for dealing with lost devices.
		*/
		void recreateDefaultPoolResources(void);

	};

	/// D3D11HardwareBufferManagerBase as a Singleton
	class D3D11HardwareBufferManager : public HardwareBufferManager
	{
	public:
		D3D11HardwareBufferManager(D3D11Device & device)
			: HardwareBufferManager(OGRE_NEW D3D11HardwareBufferManagerBase(device)) 
		{

		}
		~D3D11HardwareBufferManager()
		{
			OGRE_DELETE mImpl;
		}
	};


}


#endif
