#include "blitz.hpp"

int main(int argc, char* argv[]) {
    /* Check if all args are passed. */
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << "[-v] or [-m]" << "<gift>" << std::endl;
        std::cout << "-v --> view" << std::endl;
        std::cout << "-m --> make" << std::endl;
        return 1;
    }

    /* Check whatever option are passed. */
    int option;

    if (strcmp(argv[1], "-v") == 0) {
        option = 1;
    } else if (strcmp(argv[1], "-m") == 0) {
        option = 2;
    } else {
        std::cout << "Usage: " << argv[0] << "[-v] or [-m]" << "<gift>" << std::endl;
        std::cout << "-v --> view" << std::endl;
        std::cout << "-m --> make" << std::endl;
        return 1;
    }
    
    std::cout << "\n";
    std::cout << Blitz::logFormat("BZGN parser by CrustySeanPro & Shadów", Blitz::LogType_Info) << std::endl;

    /* View gift. */
    if (option == 1) {
        /* Open the gift file. */
        std::ifstream in(argv[2], std::ios::binary);
        if (!in) {
            std::cout << Blitz::logFormat("Failed to open gift file", Blitz::LogType_Error) << std::endl;
            std::cout << "\n";
            return 1;
        }

        /* Read header. */
        Blitz::Header header;
        in.read((char*)&header, sizeof(header));

        /* Check if header is valid. */
        if (header.m_Magic != Blitz::BZGN_MAGIC) {
            std::cout << Blitz::logFormat("Invalid file!", Blitz::LogType_Error) << std::endl;
            return -1;
        };

        Blitz::GiftGear giftGear[header.m_Count];
        /* Print details. */
        std::cout << "\n";
        std::cout << "============ GIFT DETAILS ============" << std::endl;
        std::cout << "\n";
        std::cout << "Items: " << header.m_Count << std::endl;
        std::cout << "\n";

        /* Loop through all gifts. */
        for (int i = 0; i < header.m_Count; i++) {
            std::cout << "--------------------------------------" << std::endl;
            itemstr = "Item " + std::to_string(i);
            std::cout << Blitz::logFormat(itemstr, Blitz::LogType_Warning) << std::endl;

            /* Read gift. */
            in.read((char*)&giftGear, sizeof(giftGear));

            /* Read gift into structure. */
            in >> giftGear[i].m_GiftKind;
            in >> giftGear[i].m_Kind;
            in >> giftGear[i].m_Id;
            in >> giftGear[i].field_C;

            /* Print gift. */
            std::cout << "Kind: "       << giftGear[i].m_GiftKind << std::endl;
            std::cout << "Gear kind: "  << Blitz::parseGearKind(giftGear[i].m_Kind) << std::endl;
            std::cout << "Gear id: "    << giftGear[i].m_Id << std::endl;
            std::cout << "Field_C: "    << giftGear[i].field_C << std::endl;

            std::cout << "--------------------------------------" << std::endl;

            std::cout << "\n";
            std::cout << "\n";
        }

        /* Check if all values aren't 0s. */
        if (giftGear[header.m_Count].m_GiftKind == 0 && giftGear[header.m_Count].m_Kind == 0 && giftGear[header.m_Count].m_Id == 0 && giftGear[header.m_Count].field_C == 0) {
            std::cout << Blitz::logFormat("Error in parsing gift file", Blitz::LogType_Error) << std::endl;
            std::cout << "\n";
            return 1;
        } else {
            std::cout << Blitz::logFormat("Successfully parsed gift file!", Blitz::LogType_Info) << std::endl;
            std::cout << "\n";
        }

        /* Closure line. */
        std::cout << "======================================" << std::endl;
        std::cout << "\n";

    } else if (option == 2) {
        /* Make gift. */
        std::cout << "============ GIFT MAKER ============" << std::endl;
        std::cout << "\n";
        
        /* Giftkind. */
        std::cout << "gift kind: " << std::endl;
        std::cin >> giftkind;

        /* Kind. */
        std::cout << "gear kind: " << std::endl;
        std::cin >> kind;

        /* Id. */
        std::cout << "gear id: " << std::endl;
        std::cin >> id;

        /* Not sure what is it. */
        fieldc = 0;

        /* Write gift. */
        std::ofstream out("out_gift", std::ios::binary | std::ios::app);
        if (!out) {
            std::cout << Blitz::logFormat("Failed to open output file", Blitz::LogType_Error) << std::endl;
            std::cout << "\n";
            return 1;
        }

        /* Write header. */
        Blitz::Header header {};

        /* Fill structure. */
        header.m_Magic = Blitz::BZGN_MAGIC;
        header.m_Count = 1;

        out.write((char*)&header, sizeof(header));

        /* Write gift. */
        out.write((char*)&giftkind, sizeof(giftkind));
        out.write((char*)&kind, sizeof(kind));
        out.write((char*)&id, sizeof(id));
        out.write((char*)&fieldc, sizeof(fieldc));

        /* Close file. */
        out.close();
    }

    return 0;
}