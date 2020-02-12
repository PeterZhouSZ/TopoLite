///////////////////////////////////////////////////////////////
//
// PartGroup.cpp
//
//   A group of parts
//
// by Peng SONG  ( songpenghit@gmail.com )
// 
// 16/Jan/2018
//
///////////////////////////////////////////////////////////////


#include "Utility/HelpDefine.h"
#include "Utility/GeometricPrimitives.h"
#include "Utility/HelpFunc.h"

#include "Mesh/MeshConverter.h"
#include "Mesh/PolyMesh.h"
#include "Mesh/Polygon.h"

#include "Mesh/Cross.h"
#include "Part.h"
#include "PartGroup.h"
#include "IO/InputVar.h"

#include "igl/writeOBJ.h"

//**************************************************************************************//
//                                   Initialization
//**************************************************************************************//

PartGroup::PartGroup(const vector<wpPart>& _groupParts, shared_ptr<InputVarList> var) :TopoObject(var)
{
	for (int i = 0; i < _groupParts.size(); i++)
	{
		pPart part = _groupParts[i].lock();
		if(part)
			groupParts.push_back(part);
	}
}


PartGroup::PartGroup(vector<pPart> partList, vector<int> groupPartIDs, shared_ptr<InputVarList> var):TopoObject(var)
{
	for (int i = 0; i < groupPartIDs.size(); i++)
	{
		int partID = groupPartIDs[i];

		if ( partID < 0 || partID >= partList.size() )
		{
			printf("Warning: the group partID should be within the part list. \n");
			continue;
		}

		pPart part = partList[partID];

		groupParts.push_back(part);
	}
}

PartGroup::PartGroup(vector<wpPart> partList, vector<int> groupPartIDs, shared_ptr<InputVarList> var):TopoObject(var)
{
	for (int i = 0; i < groupPartIDs.size(); i++)
	{
		int partID = groupPartIDs[i];

		if ( partID < 0 || partID >= partList.size() )
		{
			printf("Warning: the group partID should be within the part list. \n");
			continue;
		}

		wpPart part = partList[partID];

		groupParts.push_back(part);
	}
}

PartGroup::~PartGroup()
{

}


vector<Vector3f> PartGroup::GetAllVertices()
{
	vector<Vector3f> allVertices;

	for (int i = 0; i < groupParts.size(); i++)
	{
		pPolyMesh polyMesh = make_shared<PolyMesh>(*groupParts[i].lock()->polyMesh);
        polyMesh->TranslateMesh(Vector3f(0, -getVarList()->get<float>("ground_height"), 0));

		//allVertices.insert(allVertices.end(), polyMesh->verList.begin(), polyMesh->verList.end());

		for (int j = 0; j < polyMesh->vertexList.size(); j++)
		{
			allVertices.push_back(polyMesh->vertexList[j]);
		}
	}

	return allVertices;
}

vector<vector<int>> PartGroup::GetAllPolygons(const vector<Vector3f> &allVertices)
{
	vector<vector<int>> allPolys;

	for (int i = 0; i < groupParts.size(); i++)
	{
		pPolyMesh polyMesh = make_shared<PolyMesh>(*groupParts[i].lock()->polyMesh);
        polyMesh->TranslateMesh(Vector3f(0, -getVarList()->get<float>("ground_height"), 0));
		
		for (int j = 0; j < polyMesh->polyList.size(); j++)
		{
			pPolygon poly = polyMesh->polyList[j];

			// Push back one face of a part
			vector<int> polyIndices;
			for (int k = 0; k < poly->vers.size(); k++)
			{
				int index = GetPointIndexInList(poly->vers[k].pos, allVertices);

				if (index == ELEMENT_OUT_LIST)
				{
					printf("Warning: the polygon's vertex should be in the list. \n");
					continue;
				}
			
				polyIndices.push_back(index);
			}

			allPolys.push_back(polyIndices);
		}	
	}

	return allPolys;
}

//**************************************************************************************//
//                                   Write OBJ Model
//**************************************************************************************/

void PartGroup::WriteGroupOBJModel(const char *objFileName, bool triangulate)
{
    FILE *fp;
    if ((fp = fopen(objFileName, "w+")) == NULL)
    {
        printf("Error: file not exists! \n");
        return;
    }
    else
    {
        vector<Vector3f> allVertices = GetAllVertices();
        vector<vector<int>> allPolys = GetAllPolygons(allVertices);

        ////////////////////////////////////////////////////////
        // Write the vertex info of piece OBJ Part
        //fprintf(fp, "# Wavefront OBJ generated by Peng SONG \n\n");

        fprintf(fp, "# %d vertices \n", (int) allVertices.size());

        for (int i = 0; i < allVertices.size(); i++)
        {
            fprintf(fp, "v %f %f %f \n", allVertices[i].x, allVertices[i].y, allVertices[i].z);
        }
        fprintf(fp, "\n");


        ////////////////////////////////////////////////////////
        // Write the quad info of piece OBJ Part

        fprintf(fp, "# %d faces \n", (int)allPolys.size());

        for (int i = 0; i < allPolys.size(); i++)
        {
            vector<int> poly = allPolys[i];

            if(!triangulate){
                fprintf(fp, "f ");
                for (int j = 0; j < poly.size(); j++)
                {
                    //Since the index in OBJ file starting from 1 instead of 0, we need to add 1 to each index
                    fprintf(fp, " %d", poly[j] + 1);
                }
                fprintf(fp, "\n");
            }
            else{
                for(int j = 0; j < (int) poly.size() - 2; j++)
                {
                    fprintf(fp, "f ");
                    int indices[3] = {0, j + 1, j + 2};
                    for(int k = 0; k < 3; k++)
                    {
                        int verID = poly[indices[k]];
                        fprintf(fp, " %d", verID + 1);
                    }
                    fprintf(fp, "\n");
                }
            }

        }
        fprintf(fp, "\n");

        fclose(fp);

        //printf("done \n");
    }

}

void PartGroup::WriteGroupOBJWireModel(char *objFileName)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    vector<Vector3f> ver;
    vector<Vector3i> tri;
    shared_ptr<PolyMesh> wireframe;

    float thickness = getVarList()->get<float>("wireframe_thickness");
    int circle_vertex_num = getVarList()->get<int>("wireframe_circle_vertex_num");

    for(wpPart part : groupParts)
    {
        shared_ptr<HEdgeMesh> hedgeMesh = make_shared<HEdgeMesh>();
        shared_ptr<PolyMesh> mesh = make_shared<PolyMesh>(*part.lock()->polyMesh);

        hedgeMesh->InitHEdgeMesh(mesh);
        hedgeMesh->BuildHalfEdgeMesh();

        for(int id = 0; id < hedgeMesh->edgeList.size(); id++)
        {
            shared_ptr<HVertex> sta = hedgeMesh->edgeList[id]->staVer.lock();
            shared_ptr<HVertex> end = hedgeMesh->edgeList[id]->endVer.lock();
            if(sta->id < end->id)
            {
                Vector3f z_axis = (end->point - sta->point); z_axis /= len(z_axis);
                Vector3f x_axis = Vector3f(0, 1, 0) CROSS z_axis;
                if(len(x_axis) < FLOAT_ERROR_LARGE) x_axis = Vector3f(1, 0, 0) CROSS z_axis; x_axis /= len(x_axis);
                Vector3f y_axis = z_axis CROSS x_axis; y_axis /= len(y_axis);

                for(int id = 0; id < circle_vertex_num; id++)
                {
                    float angle0 = 2 * M_PI/circle_vertex_num * id;
                    float angle1 = 2 * M_PI/circle_vertex_num * (id + 1);
                    Vector3f v_sta0 = sta->point + x_axis * thickness * cos(angle0) + y_axis * thickness * sin(angle0);
                    Vector3f v_sta1 = sta->point + x_axis * thickness * cos(angle1) + y_axis * thickness * sin(angle1);
                    Vector3f v_end0 = v_sta0 + (end->point - sta->point);
                    Vector3f v_end1 = v_sta1 + (end->point - sta->point);
                    int f = ver.size();
                    ver.push_back(v_sta0);ver.push_back(v_sta1);ver.push_back(v_end0);ver.push_back(v_end1);
                    tri.push_back(Vector3i(f, f + 1, f + 2));
                    tri.push_back(Vector3i(f + 1, f + 3, f + 2));
                }
            }
        }
    }

    MeshConverter converter;
    converter.Convert2EigenMesh(ver, tri, V, F);
    igl::writeOBJ(objFileName, V, F);
}