# Notes

usage is prog04 input output numIterations where numIterations must be an integer above 0.

I tested the code on box1, torus3, kitten and kitten_lowres and it worked. Note: I was originally going to use half-edge as the data structure to store the figure in, but then the more I thought about it I thought it would be overkill, that it would be easier just to store a list of points, a list of triangles, and a list of edges, and have the code be edge-driven. It would be as thus:

Edge object:
    Two point vectors
    One or two triangle objects
        Three point vectors

Where as many of those objects as possible would be stored as pointers rather than object copies, to reduce memory footprint. What happened though, is that while that structure worked for the actual loop subdivision itself, storing the new triangles in the vector used to write the output file required me to get creative. Now, each triangle object points back to three edge objects. I'm aware this is a *highly* inefficient way to handle the data. As a result, the larger the obj file, the longer the code takes to run subdivision. torus3, one of the larger files given to us, for example, takes about two minutes to run and about 10MB of RAM. I ran kitten with numIterations 1 and it ended up going for over 20 min, whereas kitten_lowres with a paramater of two ran for about 8 minutes. This could be improved by using winged-edge or half-edge, I imagine, but I don't have it in me to rip apart my working code. Additionally, when working with this I realized that when storing values in an std::vector, as the vector grows STL moves the vector to where it can be fit in memory. This broke a lot of the pointers I was using for the Edge object (specifcally, the pointers to triangle objects). So what I do now instead is allocate space for each vector to make sure it doesn't have to move locations, so that the pointers never break. I currently have it set to 50000, as this should allow some overhead for all of the included objects, including the quite large kitten obj. This is a limitation for my code, and something else that could be addressed.

I have also completed the written questions for the undergrad assignment as well as for the grad assignment. I plan to add in the features required by the undergrad assignment later, but I cannot make any assurances any of it will actually work.

# References

I'm using this document: http://www.cs.cmu.edu/afs/cs/academic/class/15462-s14/www/lec_slides/Subdivision.pdf for guidance on the loop subdivision algorithm. It has weights of 3/8 bordering points and 1/8 opposite points for interior odd vertices, and 1/2 for boundary odd vertices.

For even vertices, I'm using the weights dictaed in this document: https://graphics.stanford.edu/~mdfisher/subdivision.html which recommends the below for the weights.

![alt text](https://graphics.stanford.edu/~mdfisher/TutorialData/SubdivStencil4.png "weights")


Sample models in Wavefront .obj format

* box{1,2}.obj are a cube at two different resolutions
* tetrahedron.obj is a tetrahedron
* torus{1,2,3}.obj are three different torii
* kitten.obj is the well known kitten model by Frank B. ter Haar, first appearing in "Frank B. ter Haar, Remco C. Veltkamp:
Automatic multiview quadruple alignment of unordered range scans. Shape Modeling International 2007: 137-146" and available from [http://visionair.ge.imati.cnr.it/ontologies/shapes/view.jsp?id=270-Kitten_-_merged](http://visionair.ge.imati.cnr.it/ontologies/shapes/view.jsp?id=270-Kitten_-_merged).
    * kitten_lowres.obj is a simplified mesh using quadric error decimation 
* bunny.obj is the well known Stanford bunny model [http://graphics.stanford.edu/data/3Dscanrep/](http://graphics.stanford.edu/data/3Dscanrep/), after repairing holes.  
    * bunny_lowres.obj is a simplified mesh using quadric error decimation
* teapot.obj is the well known Utah teapot model [https://www.sjbaker.org/wiki/index.php?title=The_History_of_The_Teapot](https://www.sjbaker.org/wiki/index.php?title=The_History_of_The_Teapot) due to Martin Newell.  Note that this model is NOT a manifold mesh.