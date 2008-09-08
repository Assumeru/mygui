/*!
	@file
	@author		Albert Semenov
	@date		09/2008
	@module
*/
#ifndef __MYGUI_RESOURCE_IMAGE_SET_H__
#define __MYGUI_RESOURCE_IMAGE_SET_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Common.h"
#include "MyGUI_XmlDocument.h"
#include "MyGUI_Resource.h"
#include "MyGUI_ImageInfo.h"

namespace MyGUI
{

	struct IndexImage
	{
		std::string name;
		float rate;
		std::vector<IntPoint> frames;
	};
	typedef std::vector<IndexImage> VectorIndexImage;

	struct GroupImage
	{
		std::string name;
		std::string texture;
		IntSize size;
		VectorIndexImage indexes;
	};

	typedef std::vector<GroupImage> VectorGroupImage;

	class _MyGUIExport ResourceImageSet : public Resource
	{
		friend class ResourceManager;

	private:
		ResourceImageSet() { }
		ResourceImageSet(xml::xmlNodeIterator _node);
		~ResourceImageSet() { }

		static void createResource(ResourcePtr & _resource, xml::xmlNodeIterator _node);

		inline size_t getGroupIndex(const std::string & _name)
		{
			for (size_t index=0; index<mGroups.size(); ++index) {
				if (mGroups[index].name == _name) return index;
			}
			return ITEM_NONE;
		}

		inline size_t getGroupIndex(const IntSize & _size)
		{
			for (size_t index=0; index<mGroups.size(); ++index) {
				if (mGroups[index].size == _size) return index;
			}
			return ITEM_NONE;
		}

		inline size_t getImageIndex(GroupImage & _group, const std::string & _name)
		{
			VectorIndexImage & indexes = _group.indexes;
			for (size_t index=0; index<indexes.size(); ++index) {
				if (indexes[index].name == _name) return index;
			}
			return ITEM_NONE;
		}

	public:
		virtual const std::string & getType();
		static const std::string & getResourceType();

		static void registryType();
		static void unregistryType();

	private:
		static std::string mType;

		//-------------------------------------------------------------//
	public:
		ImageIndexInfo getIndexInfo(const std::string & _group, const std::string & _index);
		ImageIndexInfo getIndexInfo(size_t _group, const std::string & _index);
		ImageIndexInfo getIndexInfo(const std::string & _group, size_t _index);
		ImageIndexInfo getIndexInfo(size_t _group, size_t _index);
		ImageIndexInfo getIndexInfo(const IntSize & _group, size_t _index);
		ImageIndexInfo getIndexInfo(const IntSize & _group, const std::string & _index);

	private:
		VectorGroupImage mGroups;

		static std::string mTextureEmpty;
		static IntSize mSizeEmpty;
		static std::vector<IntPoint> mFramesEmpty;

	};

} // namespace MyGUI

#endif // __MYGUI_RESOURCE_IMAGE_SET_H__
