/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include "CommandSystemConfig.h"
#include <AzCore/std/containers/vector.h>
#include <MCore/Source/Command.h>
#include "CommandManager.h"

#include <EMotionFX/Source/AnimGraphNodeId.h>
#include <EMotionFX/Source/AnimGraphStateTransition.h>
#include <EMotionFX/Source/BlendTreeConnection.h>


namespace CommandSystem
{
    // create a blend node
    MCORE_DEFINECOMMAND_START(CommandAnimGraphCreateNode, "Create a anim graph node", true)
public:
    EMotionFX::AnimGraphNodeId GetNodeId(const MCore::CommandLine& parameters);
    void DeleteGraphNode(EMotionFX::AnimGraphNode* node);

    uint32  mAnimGraphID;
    bool    mOldDirtyFlag;
    EMotionFX::AnimGraphNodeId mNodeId;
    MCORE_DEFINECOMMAND_END


    // adjust a node
    MCORE_DEFINECOMMAND_START(CommandAnimGraphAdjustNode, "Adjust a anim graph node", true)
    EMotionFX::AnimGraphNodeId mNodeId;
    int32               mOldPosX;
    int32               mOldPosY;
    AZStd::string       mOldName;
    AZStd::string       mOldParameterMask;
    bool                mOldDirtyFlag;
    bool                mOldEnabled;
    bool                mOldVisualized;
    AZStd::string       mNodeGroupName;

public:
    EMotionFX::AnimGraphNodeId GetNodeId() const    { return mNodeId; }
    const AZStd::string& GetOldName() const         { return mOldName; }
    uint32              mAnimGraphID;
    MCORE_DEFINECOMMAND_END


    // remove a node
    MCORE_DEFINECOMMAND_START(CommandAnimGraphRemoveNode, "Remove a anim graph node", true)
    EMotionFX::AnimGraphNodeId mNodeId;
    uint32          mAnimGraphID;
    EMotionFX::AnimGraphNodeId mParentNodeId;
    AZ::TypeId      mType;
    AZStd::string   mParentName;
    AZStd::string   mName;
    AZStd::string   mNodeGroupName;
    int32           mPosX;
    int32           mPosY;
    AZStd::string   mOldContents;
    bool            mCollapsed;
    bool            mOldDirtyFlag;
    bool            mIsEntryNode;

public:
    EMotionFX::AnimGraphNodeId GetNodeId() const        { return mNodeId; }
    EMotionFX::AnimGraphNodeId GetParentNodeId() const  { return mParentNodeId; }
    MCORE_DEFINECOMMAND_END


    // set the entry state of a state machine
    MCORE_DEFINECOMMAND_START(CommandAnimGraphSetEntryState, "Set entry state", true)
public:
    uint32                      mAnimGraphID;
    EMotionFX::AnimGraphNodeId  mOldEntryStateNodeId;
    EMotionFX::AnimGraphNodeId  mOldStateMachineNodeId;
    bool                        mOldDirtyFlag;
    MCORE_DEFINECOMMAND_END


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Helper functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    COMMANDSYSTEM_API void CreateAnimGraphNode(EMotionFX::AnimGraph* animGraph, const AZ::TypeId& type, const AZStd::string& namePrefix, EMotionFX::AnimGraphNode* parentNode, int32 offsetX, int32 offsetY, const AZStd::string& serializedContents = "");

    COMMANDSYSTEM_API void DeleteNodes(EMotionFX::AnimGraph* animGraph, const AZStd::vector<AZStd::string>& nodeNames);
    COMMANDSYSTEM_API void DeleteNodes(MCore::CommandGroup* commandGroup, EMotionFX::AnimGraph* animGraph, const AZStd::vector<AZStd::string>& nodeNames, AZStd::vector<EMotionFX::AnimGraphNode*>& nodeList, AZStd::vector<EMotionFX::BlendTreeConnection*>& connectionList, AZStd::vector<EMotionFX::AnimGraphStateTransition*>& transitionList, bool autoChangeEntryStates = true);

    COMMANDSYSTEM_API void ConstructCopyAnimGraphNodesCommandGroup(MCore::CommandGroup* commandGroup, EMotionFX::AnimGraphNode* targetNode, AZStd::vector<EMotionFX::AnimGraphNode*>& inOutNodesToCopy, int32 posX, int32 posY, bool cutMode, AZStd::unordered_map<EMotionFX::AnimGraphNode*, AZStd::string>& newNamesByCopiedNodes, bool ignoreTopLevelConnections);
} // namespace CommandSystem