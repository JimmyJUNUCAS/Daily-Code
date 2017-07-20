EncoderPhaseShift3::EncoderPhaseShift3(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){

    // Set N
    N = 3;
    // Precompute encoded patterns
    const float pi = M_PI;
    for(unsigned int i=0; i<N; i++){
        float phase = 2.0*pi/float(N) * i;
        float pitch = screenCols;
        // Loop through vector
        cv::Mat phaseVector(screenCols, 1, CV_32F);
        for(int i=0; i<phaseVector.rows; i++){
            // Amplitude of channels
            float amp = 0.5*(1+cos(2*pi*i/pitch - phase));
            phaseVector.at<float>(i, 0) = amp;
        }
        // matrix transposition by means of matrix expressions(mn->nm)
        phaseVector = phaseVector.t();
        // Repeat pattern
        // 感觉像是在进行phaseVector的转换
        phaseVector = cv::repeat(phaseVector, screenRows, 1);
        phaseVector.convertTo(phaseVector, CV_8U, 255.0);
        // Repeat texture
        cv::Mat patternI(screenRows, screenCols, CV_8UC3);
        cv::cvtColor(phaseVector, patternI, cv::COLOR_GRAY2RGB);
        patterns.push_back(patternI);
    }
}

EncoderPhaseShift4::EncoderPhaseShift4(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){
    // Set N
    N = 4;
    // Precompute encoded patterns
    const float pi = M_PI;
    for(unsigned int i=0; i<N; i++){
        float phase = 2.0*pi/float(N) * i;
        float pitch = screenCols;
        cv::Mat patternI = pstools::computePhaseVector(screenCols, phase, pitch);
        patterns.push_back(patternI.t());
    }
}
    cv::Mat computePhaseVector(unsigned int length, float phase, float pitch) {

        cv::Mat phaseVector(length, 1, CV_8UC3);

        const float pi = M_PI;

        // Loop through vector
        for (int i = 0; i < phaseVector.rows; i++) {
            // Amplitude of channels
            float amp = 0.5*(1 + cos(2 * pi*i / pitch - phase));
            phaseVector.at<cv::Vec3b>(i, 0) = cv::Vec3b(255.0*amp, 255.0*amp, 255.0*amp);
        }

        return phaseVector;
    }

EncoderPhaseShift3FastWrap::EncoderPhaseShift3FastWrap(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){
    // Set N
    N = 3;
    // Precompute encoded patterns
    const float pi = M_PI;
    for(unsigned int i=0; i<N; i++){
        float phase = 2.0*pi/float(N) * i;
        float pitch = screenCols;
        cv::Mat patternI = pstools::computePhaseVector(screenCols, phase, pitch);
        patterns.push_back(patternI.t());
    }
}
EncoderPhaseShift3Unwrap::EncoderPhaseShift3Unwrap(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){
    // Set N
    this->N = 3;
    // Precompute encoded patterns
    const float pi = M_PI;
    // Horizontally encoding patterns
    for(unsigned int i=0; i<3; i++){
        float phase = 2.0*pi/3.0 * i;
        float pitch = (float)screenCols/(float)nPhases;
        cv::Mat patternI(1,1,CV_8U);
        patternI = pstools::computePhaseVector(screenCols, phase, pitch);
        patterns.push_back(patternI.t());
    }

}

EncoderPhaseShift2x3::EncoderPhaseShift2x3(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){

    // Set N
    if(dir == CodecDirBoth)
        N = 12;
    else
        N = 6;

    // Precompute encoded patterns
    const float pi = M_PI;

    if(dir & CodecDirHorizontal){
        // Horizontally encoding patterns
        for(unsigned int i=0; i<3; i++){
            float phase = 2.0*pi/3.0 * i;
            float pitch = (float)screenCols/(float)nPhases;
            cv::Mat patternI(1,1,CV_8U);
            patternI = pstools::computePhaseVector(screenCols, phase, pitch);
            patternI = patternI.t();
            patterns.push_back(patternI);
        }

        // Phase cue patterns
        for(unsigned int i=0; i<3; i++){
            float phase = 2.0*pi/3.0 * i;
            float pitch = screenCols;
            cv::Mat patternI;
            patternI = pstools::computePhaseVector(screenCols, phase, pitch);
            patternI = patternI.t();
            patterns.push_back(patternI);
        }
    }
    if(dir & CodecDirVertical){
        // Precompute vertically encoding patterns
        for(unsigned int i=0; i<3; i++){
            float phase = 2.0*pi/3.0 * i;
            float pitch = (float)screenRows/(float)nPhases;
            cv::Mat patternI;
            patternI = pstools::computePhaseVector(screenRows, phase, pitch);
            patterns.push_back(patternI);
        }

        // Precompute vertically phase cue patterns
        for(unsigned int i=0; i<3; i++){
            float phase = 2.0*pi/3.0 * i;
            float pitch = screenRows;
            cv::Mat patternI;
            patternI = pstools::computePhaseVector(screenRows, phase, pitch);
            patterns.push_back(patternI);
        }
    }
}

EncoderGrayCodeAndPhaseShift::EncoderGrayCodeAndPhaseShift(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir)
    : Encoder(_screenCols, _screenRows, _dir)
{
    N = 2;
    int phaseNum = 4;
    const float pi = M_PI;

    // Set total pattern number
    if (dir & CodecDirHorizontal)
        this->N += Nhorz * 2 + phaseNum;

    if (dir & CodecDirVertical)
        this->N += Nvert * 2 + phaseNum;

    // Encode every pixel column
    int NbitsHorz = ceilf(log2f((float)screenCols));

    // Number of vertical encoding patterns
    int NbitsVert = ceilf(log2f((float)screenRows));

    cv::Mat patternOn(1, 1, CV_8UC3, cv::Scalar(0));
    patternOn.at<cv::Vec3b>(0, 0) = cv::Vec3b(255, 255, 255);
    patterns.push_back(patternOn);
    
    cv::Mat patternOff(1, 1, CV_8UC3, cv::Scalar(0));
    patterns.push_back(patternOff);

    if (dir & CodecDirHorizontal) {
        // Precompute horizontally encoding patterns
        for (unsigned int p = 0; p < Nhorz; p++) {
            cv::Mat patternP(1, screenCols, CV_8UC3);
            cv::Mat patternN(1, screenCols, CV_8UC3);
            // Loop through columns in first row
            for (unsigned int j = 0; j < screenCols; j++) {
                unsigned int jGray = binaryToGray(j);
                // Amplitude of channels
                float amp = get_bit(jGray, NbitsHorz - p);
                float rev = 1 - amp;
                patternP.at<cv::Vec3b>(0, j) = cv::Vec3b(255.0*amp, 255.0*amp, 255.0*amp);
                patternN.at<cv::Vec3b>(0, j) = cv::Vec3d(255.0*rev, 255.0*rev, 255.0*rev);
            }
            patterns.push_back(patternP);
            patterns.push_back(patternN);
        }

        // Horizontally encoding patterns
        for (unsigned int i = 0; i < phaseNum; i++) {
            float phase = 2.0*pi / float(phaseNum) * i;
            float pitch = (float)screenCols / (float)nPhases;
            cv::Mat patternI(1, 1, CV_8U);
            patternI = pstools::computePhaseVector(screenCols, phase, pitch);
            patternI = patternI.t();
            patterns.push_back(patternI);
        }
    }
    if (dir & CodecDirVertical) {
        // Precompute vertical encoding patterns
        for (unsigned int p = 0; p < Nvert; p++) {
            cv::Mat patternP(screenRows, 1, CV_8UC3);

            // Loop through rows in first column
            for (unsigned int i = 0; i < screenRows; i++) {
                unsigned int iGray = binaryToGray(i);
                // Amplitude of channels
                float amp = get_bit(iGray, NbitsVert - p);
                patternP.at<cv::Vec3b>(i, 0) = cv::Vec3b(255.0*amp, 255.0*amp, 255.0*amp);
            }
            patterns.push_back(patternP);
        }

        // Precompute vertically encoding patterns
        for (unsigned int i = 0; i < phaseNum; i++) {
            float phase = 2.0*pi / float(phaseNum) * i;
            float pitch = (float)screenRows / (float)nPhases;
            cv::Mat patternI;
            patternI = pstools::computePhaseVector(screenRows, phase, pitch);
            patterns.push_back(patternI);
        }
    }
}
EncoderGrayCode::EncoderGrayCode(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){

    N = 2;

    // Set total pattern number
    if(dir & CodecDirHorizontal)
        this->N += Nhorz;

    if(dir & CodecDirVertical)
        this->N += Nvert;

    // Encode every pixel column
    int NbitsHorz = ceilf(log2f((float)screenCols));

    // Number of vertical encoding patterns
    int NbitsVert = ceilf(log2f((float)screenRows));

    cv::Mat patternOn(1, 1, CV_8UC3, cv::Scalar(0));
    patternOn.at<cv::Vec3b>(0,0) = cv::Vec3b(255, 255, 255);
    patterns.push_back(patternOn);

    cv::Mat patternOff(1, 1, CV_8UC3, cv::Scalar(0));
    patterns.push_back(patternOff);

    if(dir & CodecDirHorizontal){
        // Precompute horizontally encoding patterns
        for(unsigned int p=0; p<Nhorz; p++){
            cv::Mat patternP(1, screenCols, CV_8UC3);
            // Loop through columns in first row
            for(unsigned int j=0; j<screenCols; j++){
                unsigned int jGray = binaryToGray(j);
                // Amplitude of channels
                float amp = get_bit(jGray, NbitsHorz-p);
                patternP.at<cv::Vec3b>(0,j) = cv::Vec3b(255.0*amp,255.0*amp,255.0*amp);
            }
            patterns.push_back(patternP);
        }
    }
    if(dir & CodecDirVertical){
        // Precompute vertical encoding patterns
        for(unsigned int p=0; p<Nvert; p++){
            cv::Mat patternP(screenRows, 1, CV_8UC3);

            // Loop through rows in first column
            for(unsigned int i=0; i<screenRows; i++){

                unsigned int iGray = binaryToGray(i);

                // Amplitude of channels
                float amp = get_bit(iGray, NbitsVert-p);
                patternP.at<cv::Vec3b>(i,0) = cv::Vec3b(255.0*amp,255.0*amp,255.0*amp);
            }
            patterns.push_back(patternP);
        }
    }

    #if 0
        for(unsigned int i=0; i<patterns.size(); i++){
            std::stringstream fileNameStream;
            fileNameStream << "pattern_" << std::setw(2) << std::setfill('0') << i << ".bmp";
            cv::imwrite(fileNameStream.str(), patterns[i]);
        }

    #endif
}