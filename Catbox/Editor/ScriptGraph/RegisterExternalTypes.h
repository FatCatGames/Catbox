﻿#pragma once
// Place your includes for registered types here.
#include <cinttypes>

#include "ScriptGraph/ScriptGraphTypes.h"

/********************************************************************************************************************************
 *
 * Here you should declare all types that the ScriptGraph should be aware of. I.e. all
 * types that can appear as a Pin on a Script Graph Node or as a Variable.
 *
 * Format goes:
 * BeginDataTypeHandler(...)
 * <specific code or nothing at all>
 * EndDataTypeHandler
 *
 * BeginDataTypeHandler(FriendlyName, Type, Color, InPlaceConstructible)
 * - FriendlyName is the name you will see in the UI for this type.
 * - Type is the C++ type itself, like float, std::string, GameObject* etc.
 * - Color is the color which will be used to identify this type of variable.
 * - InPlaceConstructible is if we can create this type with a ImGui widget or not
 *   during runtime. You MUST override RenderconstructWidget between Begin and End for
 *	 this to work. See examples below.
 *
 * You can override methods found in the base class:
 * void RenderConstructWidget(const std::string& aContainerUUID, void* aDataPtr, const ScriptGraphType& aTypeInfo) override
 * - This should draw an ImGui widget to edit the provided data pointer.
 *
 * std::string ToString(const void* aDataPtr, const ScriptGraphType& aTypeInfo) const override
 * - This should return a string representation of the data, useful for showing default
 *   values in the UI or other things. Allows calling of ScriptGraphDataTypeRegistry::GetString
 *   to get an easily loggable representation of the contents in a data container.
 *
 * virtual void SerializeData(const void* aDataPtr, const ScriptGraphType& aTypeInfo, std::vector<uint8_t>& outData) const
 * - If, and only if, you need to handle serialization of your data type on your own. The default serializer works for all
 *   POD types, but if you want to serialize pointers and things you need to do this yourself :).
 *
 * virtual void DeserializeData(const std::vector<uint8_t>& inData, const ScriptGraphType& aTypeInfo, void* outDataPtr) const
  - If, and only if, you need to handle deserialization of your data type on your own. The default deserializer works for all
 *  POD types, but if you want to deserialize pointers and things you need to do this yourself :).
 *
 *******************************************************************************************************************************/

BeginDataTypeHandler(Int, int, ImVec4(0, 128, 128, 255), true)
void RenderConstructWidget(const std::string& aContainerUUID, void* aDataPtr, const ScriptGraphType& aTypeInfo) override
{
	const float y = ImGui::GetCursorPosY();
	ImGui::SetCursorPosY(y - 2);
	const ImVec2 inputSize = ImGui::CalcTextSize("1000");
	ImGui::SetNextItemWidth(inputSize.x);
	ImGui::InputInt(aContainerUUID.c_str(), (int*)aDataPtr, 0, 0);
}

std::string ToString(const void* aDataPtr, const ScriptGraphType& aTypeInfo) const override
{
	return std::to_string(*(const int*)aDataPtr);
}
EndDataTypeHandler


#pragma region Vector3f
BeginDataTypeHandler(Vector3f, Vector3f, ImVec4(181, 230, 29, 255), true)
void RenderConstructWidget(const std::string& aContainerUUID, void* aDataPtr, const ScriptGraphType& aTypeInfo) override
{
	const float y = ImGui::GetCursorPosY();
	ImGui::SetCursorPosY(y - 2);
	const ImVec2 inputSize = ImGui::CalcTextSize("0.0000");
	ImGui::SetNextItemWidth(inputSize.x);
	Catbox::DragFloat3(aContainerUUID.c_str(), (Vector3f*)aDataPtr, 0, 0);
}

std::string ToString(const void* aDataPtr, const ScriptGraphType& aTypeInfo) const override
{
	std::string s;
	Vector3f vec = *(Vector3f*)aDataPtr;
	s = std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z);
	return s;
}

EndDataTypeHandler
#pragma endregion
