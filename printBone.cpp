/*
 * File: /printBone.cpp
 * Created Date: Wednesday November 15th 2023
 * Author: Zihan
 * -----
 * Last Modified: Wednesday, 15th November 2023 2:40:42 pm
 * Modified By: the developer formerly known as Zihan at <wzh4464@gmail.com>
 * -----
 * HISTORY:
 * Date      		By   	Comments
 * ----------		------	---------------------------------------------------------
 * 15-11-2023		Zihan	Added printBone.cpp, print bone names and positions to `bones.txt`
 */

#include <fbxsdk.h>
#include <stdio.h>

using namespace fbxsdk;

void PrintBoneNames(fbxsdk::FbxNode *pNode, FILE *file)
{
    if (pNode->GetNodeAttribute() && pNode->GetNodeAttribute()->GetAttributeType() == fbxsdk::FbxNodeAttribute::eSkeleton)
    {
        fbxsdk::FbxSkeleton *skeleton = (fbxsdk::FbxSkeleton *)pNode->GetNodeAttribute();
        fbxsdk::FbxString name = skeleton->GetName();
        fbxsdk::FbxVector4 lT = pNode->LclTranslation.Get();
        fprintf(file, "%s\n", name.Buffer());
        fprintf(file, "%f, %f, %f\n", lT[0], lT[1], lT[2]);
    }

    const int lChildCount = pNode->GetChildCount();
    for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
    {
        PrintBoneNames(pNode->GetChild(lChildIndex), file);
    }
}

int main(int argc, char **argv)
{
    fbxsdk::FbxManager *lSdkManager = fbxsdk::FbxManager::Create();
    fbxsdk::FbxIOSettings *ios = fbxsdk::FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    fbxsdk::FbxImporter *lImporter = fbxsdk::FbxImporter::Create(lSdkManager, "");

    // default char* lFilename to be "Assets/Characters/Jean/Jean.fbx", but you can change it with command line

    const char *lFilename = "Assets/Characters/Jean/Jean.fbx";
    if (argc > 1)
    {
        lFilename = argv[1];
    }

    // print the file name
    printf("FBX 文件名: %s\n", lFilename);

    if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
    {
        printf("无法初始化 FBX 导入器: %s\n", lImporter->GetStatus().GetErrorString());
        exit(-1);
    }

    fbxsdk::FbxScene *lScene = fbxsdk::FbxScene::Create(lSdkManager, "My Scene");
    lImporter->Import(lScene);
    lImporter->Destroy();
    // 在这里打开文件以便写入
    FILE *file = fopen("bones.txt", "w");
    if (!file)
    {
        perror("无法打开文件");
        return -1;
    }

    fbxsdk::FbxNode *lRootNode = lScene->GetRootNode();
    if (lRootNode)
    {
        PrintBoneNames(lRootNode, file);
    }

    // 关闭文件
    fclose(file);

    lSdkManager->Destroy();
    return 0;
}
