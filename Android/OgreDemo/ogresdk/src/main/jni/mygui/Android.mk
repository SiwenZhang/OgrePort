LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES	:= \
			$(LOCAL_PATH)/../ogre \
			$(LOCAL_PATH)/../common \
            $(MYGUI_ROOT)/MyGUIEngine/include \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/include \
            $(OGRE_ROOT)/OgreMain/include \
            $(FREETYPE_ROOT)/include \

LOCAL_SRC_FILES := \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ActionController.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Any.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_BackwardCompatibility.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_BiIndexBase.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Button.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Canvas.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ChildSkinInfo.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Colour.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ComboBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ConsoleLogListener.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Constants.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ControllerEdgeHide.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ControllerFadeAlpha.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ControllerManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ControllerPosition.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ControllerRepeatClick.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ClipboardManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DataFileStream.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DataManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DataMemoryStream.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DataStream.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DDContainer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DynLib.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_DynLibManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_EditBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_EditText.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Exception.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_FactoryManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_FileLogListener.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_FontManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_GeometryUtility.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Gui.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ImageBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_InputManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ItemBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LanguageManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LayerItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LayerManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LayerNode.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LayoutManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LevelLogFilter.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ListBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LogManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_LogSource.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MainSkin.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MaskPickInfo.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MenuBar.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MenuControl.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MenuItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MultiListBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_MultiListItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_OverlappedLayer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_PluginManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_PointerManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_PolygonalSkin.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_PopupMenu.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Precompiled.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ProgressBar.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_RenderItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_RenderManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceImageSet.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceImageSetPointer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceLayout.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceManualFont.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceManualPointer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceSkin.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ResourceTrueTypeFont.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_RotatingSkin.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ScrollBar.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ScrollView.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ScrollViewBase.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SharedLayer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SharedLayerNode.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SimpleText.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SkinItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SkinManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SubSkin.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SubWidgetBinding.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_SubWidgetManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TabControl.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TabItem.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TextBox.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TextIterator.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TextureUtility.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TextView.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_TileRect.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Timer.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_ToolTipManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_UString.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Widget.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_WidgetInput.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_WidgetManager.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_WidgetUserData.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_Window.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_WindowsClipboardHandler.cpp \
            $(MYGUI_ROOT)/MyGUIEngine/src/MyGUI_XmlDocument.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreDataManager.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreDataStream.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreRenderManager.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreRTTexture.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreTexture.cpp \
            $(MYGUI_ROOT)/Platforms/Ogre/OgrePlatform/src/MyGUI_OgreVertexBuffer.cpp \

LOCAL_MODULE := libmygui

LOCAL_CFLAGS += -O3 -DUSE_MMAP -DMYGUI_USE_FREETYPE -DDEBUG

include $(BUILD_STATIC_LIBRARY)

