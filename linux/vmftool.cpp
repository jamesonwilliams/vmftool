#include <fstream>
#include <iostream>
#include <string.h>
#include <vmf.hpp>

#define METADATA_NAME_STRING "vmftool"

void readData(std::string video_path) {
    vmf::initialize();

    // Read message from file
    const std::string METADATA_NAME(METADATA_NAME_STRING);
    vmf::MetadataStream inStream;

    if (!inStream.open(video_path, vmf::MetadataStream::ReadOnly)) {
        std::cerr << "couldn't open the video file." << std::endl;
        vmf::terminate();
        return;
    }

    inStream.load();
    vmf::MetadataSet testMetadata = inStream.queryByName(METADATA_NAME);
    if (!testMetadata.empty()) {
        std::string readMessage = (std::string) testMetadata.at(0)->at(0);
        std::cout << readMessage;
    } else {
        std::cerr << "no metadata." << std::endl;
    }

    inStream.close();
    vmf::terminate();
}

void writeData(std::string video_path, std::string data_path) {
    // Load the metadata as a string.
    std::ifstream ifs(data_path);
    std::string metadata;
    metadata.assign((std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>()));
    ifs.close();

    vmf::initialize();

    // Write metadata out to file.
    vmf::MetadataStream outStream;

    if (!outStream.open(video_path, vmf::MetadataStream::ReadWrite)) {
        std::cerr << "Couldn't open video file " << video_path << std::endl;
        vmf::terminate();
        return;
    }

    const std::string SCHEMA_NAME(METADATA_NAME_STRING);
    std::shared_ptr<vmf::MetadataSchema> schema =
        std::make_shared<vmf::MetadataSchema>(SCHEMA_NAME);
    const std::string METADATA_NAME(METADATA_NAME_STRING);
    std::shared_ptr<vmf::MetadataDesc> desc =
        std::make_shared<vmf::MetadataDesc>(METADATA_NAME,
                                            vmf::Variant::type_string);
    schema->add(desc);
    try {
        outStream.addSchema(schema);
    } catch (...) {
        std::cerr << "Failed to add schema." << std::endl;
        outStream.close();
        vmf::terminate();
        return;
    }

    std::shared_ptr<vmf::Metadata> metadataForSaving =
        std::make_shared<vmf::Metadata>(desc);
    metadataForSaving->addValue(metadata);

    outStream.add(metadataForSaving);
    if (!outStream.save()) {
        std::cerr << "Couldn't save message to file.." << std::endl;
    }

    outStream.close();
    vmf::terminate();
}

int main(int argc, char *argv[], char *envp[]) {
    std::string video_path;
    std::string data_path;

    if (argc == 3 && 0 == strcmp(argv[1], "--read")) {
        video_path = argv[2];
        readData(video_path);
    } else if (argc == 4 && 0 == strcmp(argv[1], "--write")) {
        video_path = argv[2];
        data_path = argv[3];
        writeData(video_path, data_path);
    } else {
        std::cerr << argv[0] << " --write <video_path> <data_path>" << std::endl
                  << argv[0] << " --read <video_path>" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

