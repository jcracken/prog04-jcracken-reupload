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

# References

I'm using this document: http://www.cs.cmu.edu/afs/cs/academic/class/15462-s14/www/lec_slides/Subdivision.pdf for guidance on the loop subdivision algorithm. It has weights of 3/8 bordering points and 1/8 opposite points for interior odd vertices, and 1/2 for boundary odd vertices.

For even vertices, I'm using the weights dictaed in this document: https://graphics.stanford.edu/~mdfisher/subdivision.html which recommends ![alt text](https://graphics.stanford.edu/~mdfisher/TutorialData/SubdivStencil4.png "weights")

for the weights