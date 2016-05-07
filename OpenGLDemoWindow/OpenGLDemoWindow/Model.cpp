#include "Model.h"



Model::Model()
{
	// set the defaults to zero
	vertArr = 0;
	vertCount = 0;
}


bool Model::buffer(string objFile)
{
	// declare 4 vectors, locations, uvs, normals, and indecies
	vector<vec3> locations;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<VertInd> inds;

	// read in the string object
	ifstream inFile;

	// this checks if the file loaded properly
	inFile.open(objFile);

	// this variable will hold the string for the line in the file
	string line;

	// make a loop that will go until the file is empty
	while (getline(inFile, line))
	{ 
		string lineLabel;

		// turn the current line into a stream
		istringstream sStream(line);

		// assign each character to the line label
		sStream >> lineLabel;

		if (lineLabel == "v")
		{
			// make a small array of floats to hold the next three characters
			float locs[3];

			// assign values to the locs using sStream
			sStream >> locs[0];
			sStream >> locs[1];
			sStream >> locs[2];

			// add a new vertex cooresponding to those values
			locations.push_back(vec3(locs[0], locs[1], locs[2]));
		}

		if (lineLabel == "vt")
		{
			// make a small array of floats to hold the next three characters
			float locs[2];

			// assign values to the locs using sStream
			sStream >> locs[0];
			sStream >> locs[1];

			// add a new vertex cooresponding to those values
			uvs.push_back(vec2(locs[0], locs[1]));
		}

		if (lineLabel == "vn")
		{
			// make a small array of floats to hold the next three characters
			float locs[3];

			// assign values to the locs using sStream
			sStream >> locs[0];
			sStream >> locs[1];
			sStream >> locs[2];

			// add a new vertex cooresponding to those values
			normals.push_back(vec3(locs[0], locs[1], locs[2]));
		}

		if (lineLabel == "f")
		{
			unsigned int ints[3];
			char slashes;

			for (int i = 0; i < 3; i++)
			{
				sStream >> ints[i];
				sStream >> slashes;
			}

			ints[0]--;
			ints[1]--;
			ints[2]--;

			// assign the ints to the vertInds
			VertInd vertInd;
			vertInd.locInd = ints[0];
			vertInd.uvInd = ints[1];
			vertInd.normInd = ints[2];

			// assign that vertInd to the vector
			inds.push_back(vertInd);
		}
	}

	// close the file
	inFile.close();
	
	// define the vertex locations
	//vector<vec3> locs =
	//{
	//	{ 1, 1, 0 },
	//	{ -1, 1, 0 },
	//	{ -1, -1, 0 },
	//	{ 1, -1, 0 }
	//};
	//
	//// connecting the dots
	//vector <unsigned int>
	//	locInds =
	//{ 0, 1, 2, 0, 2, 3 };
	//
	//// add UV locations and vertices
	//vector <vec2> uvs
	//{
	//	{ 1, 1 },
	//	{ 0, 1 },
	//	{ 0, 0 },
	//	{ 1, 0 }
	//};
	//
	//// connect UV dots
	//vector <unsigned int>
	//	uvInds =
	//{ 0, 1, 2, 0, 2, 3 };

	// assign vertCount
	vertCount = inds.size();

	// duplicate the vertices into a single buffer
	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		//vertBufData[i].loc = locs[locInds[i]];
		//vertBufData[i].uv = uvs[uvInds[i]];
		//vertBufData[i].normal = 
		
		vertBufData[i] = {
			locations[inds[i].locInd],
			uvs[inds[i].uvInd],
			normals[inds[i].normInd]
		};

	}

	GLuint vertBuf;

	// generate the vertex arrays and buffers
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// bind both of them
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	// enable the attribute
	glEnableVertexAttribArray(0);

	// location attribute
	glVertexAttribPointer(
		0, // attribute index
		3, // number of components (x, y, z)
		GL_FLOAT, // type of data
		GL_FALSE, // normalize data?
		sizeof(Vertex), // stride (bytes per vertex)
		0); // offset to this attribute

			// enable the attribute
	glEnableVertexAttribArray(1);

	// uv attribute
	glVertexAttribPointer(
		1, // attribute index
		2, // number of components (x, y)
		GL_FLOAT, // type of data
		GL_FALSE, // normalize data?
		sizeof(Vertex), // stride (bytes per vertex)
		(void*)sizeof(vec3)); // offset to this attribute

							  // unbind when finished
	glBindVertexArray(0);

	// set the color to cornflower blue, #throwbackthursday
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

void Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}

Model::~Model()
{
}
