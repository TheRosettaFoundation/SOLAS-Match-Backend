// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ArchivedProject.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* ArchivedProject_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ArchivedProject_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ArchivedProject_2eproto() {
  protobuf_AddDesc_ArchivedProject_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ArchivedProject.proto");
  GOOGLE_CHECK(file != NULL);
  ArchivedProject_descriptor_ = file->message_type(0);
  static const int ArchivedProject_offsets_[13] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, title_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, description_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, impact_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, deadline_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, organisationid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, reference_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, wordcount_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, createdtime_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, languagecode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, countrycode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, archiveddate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, translatorid_),
  };
  ArchivedProject_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ArchivedProject_descriptor_,
      ArchivedProject::default_instance_,
      ArchivedProject_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ArchivedProject, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ArchivedProject));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ArchivedProject_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ArchivedProject_descriptor_, &ArchivedProject::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ArchivedProject_2eproto() {
  delete ArchivedProject::default_instance_;
  delete ArchivedProject_reflection_;
}

void protobuf_AddDesc_ArchivedProject_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025ArchivedProject.proto\"\215\002\n\017ArchivedProj"
    "ect\022\n\n\002id\030\001 \002(\005\022\r\n\005title\030\002 \001(\t\022\023\n\013descri"
    "ption\030\003 \001(\t\022\016\n\006impact\030\004 \001(\t\022\020\n\010deadline\030"
    "\005 \001(\t\022\026\n\016organisationId\030\006 \001(\005\022\021\n\treferen"
    "ce\030\007 \001(\t\022\021\n\twordCount\030\010 \001(\005\022\023\n\013createdTi"
    "me\030\t \001(\t\022\024\n\014languageCode\030\n \001(\t\022\023\n\013countr"
    "yCode\030\013 \001(\t\022\024\n\014archivedDate\030\014 \001(\t\022\024\n\014tra"
    "nslatorId\030\r \001(\005", 295);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ArchivedProject.proto", &protobuf_RegisterTypes);
  ArchivedProject::default_instance_ = new ArchivedProject();
  ArchivedProject::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ArchivedProject_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ArchivedProject_2eproto {
  StaticDescriptorInitializer_ArchivedProject_2eproto() {
    protobuf_AddDesc_ArchivedProject_2eproto();
  }
} static_descriptor_initializer_ArchivedProject_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int ArchivedProject::kIdFieldNumber;
const int ArchivedProject::kTitleFieldNumber;
const int ArchivedProject::kDescriptionFieldNumber;
const int ArchivedProject::kImpactFieldNumber;
const int ArchivedProject::kDeadlineFieldNumber;
const int ArchivedProject::kOrganisationIdFieldNumber;
const int ArchivedProject::kReferenceFieldNumber;
const int ArchivedProject::kWordCountFieldNumber;
const int ArchivedProject::kCreatedTimeFieldNumber;
const int ArchivedProject::kLanguageCodeFieldNumber;
const int ArchivedProject::kCountryCodeFieldNumber;
const int ArchivedProject::kArchivedDateFieldNumber;
const int ArchivedProject::kTranslatorIdFieldNumber;
#endif  // !_MSC_VER

ArchivedProject::ArchivedProject()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ArchivedProject::InitAsDefaultInstance() {
}

ArchivedProject::ArchivedProject(const ArchivedProject& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ArchivedProject::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  description_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  impact_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  deadline_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  organisationid_ = 0;
  reference_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  wordcount_ = 0;
  createdtime_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  languagecode_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  countrycode_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  archiveddate_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  translatorid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ArchivedProject::~ArchivedProject() {
  SharedDtor();
}

void ArchivedProject::SharedDtor() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (description_ != &::google::protobuf::internal::kEmptyString) {
    delete description_;
  }
  if (impact_ != &::google::protobuf::internal::kEmptyString) {
    delete impact_;
  }
  if (deadline_ != &::google::protobuf::internal::kEmptyString) {
    delete deadline_;
  }
  if (reference_ != &::google::protobuf::internal::kEmptyString) {
    delete reference_;
  }
  if (createdtime_ != &::google::protobuf::internal::kEmptyString) {
    delete createdtime_;
  }
  if (languagecode_ != &::google::protobuf::internal::kEmptyString) {
    delete languagecode_;
  }
  if (countrycode_ != &::google::protobuf::internal::kEmptyString) {
    delete countrycode_;
  }
  if (archiveddate_ != &::google::protobuf::internal::kEmptyString) {
    delete archiveddate_;
  }
  if (this != default_instance_) {
  }
}

void ArchivedProject::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ArchivedProject::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ArchivedProject_descriptor_;
}

const ArchivedProject& ArchivedProject::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ArchivedProject_2eproto();  return *default_instance_;
}

ArchivedProject* ArchivedProject::default_instance_ = NULL;

ArchivedProject* ArchivedProject::New() const {
  return new ArchivedProject;
}

void ArchivedProject::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0;
    if (has_title()) {
      if (title_ != &::google::protobuf::internal::kEmptyString) {
        title_->clear();
      }
    }
    if (has_description()) {
      if (description_ != &::google::protobuf::internal::kEmptyString) {
        description_->clear();
      }
    }
    if (has_impact()) {
      if (impact_ != &::google::protobuf::internal::kEmptyString) {
        impact_->clear();
      }
    }
    if (has_deadline()) {
      if (deadline_ != &::google::protobuf::internal::kEmptyString) {
        deadline_->clear();
      }
    }
    organisationid_ = 0;
    if (has_reference()) {
      if (reference_ != &::google::protobuf::internal::kEmptyString) {
        reference_->clear();
      }
    }
    wordcount_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (has_createdtime()) {
      if (createdtime_ != &::google::protobuf::internal::kEmptyString) {
        createdtime_->clear();
      }
    }
    if (has_languagecode()) {
      if (languagecode_ != &::google::protobuf::internal::kEmptyString) {
        languagecode_->clear();
      }
    }
    if (has_countrycode()) {
      if (countrycode_ != &::google::protobuf::internal::kEmptyString) {
        countrycode_->clear();
      }
    }
    if (has_archiveddate()) {
      if (archiveddate_ != &::google::protobuf::internal::kEmptyString) {
        archiveddate_->clear();
      }
    }
    translatorid_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ArchivedProject::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_title;
        break;
      }
      
      // optional string title = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_title:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_title()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->title().data(), this->title().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_description;
        break;
      }
      
      // optional string description = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_description:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_description()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->description().data(), this->description().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_impact;
        break;
      }
      
      // optional string impact = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_impact:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_impact()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->impact().data(), this->impact().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_deadline;
        break;
      }
      
      // optional string deadline = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_deadline:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_deadline()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->deadline().data(), this->deadline().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_organisationId;
        break;
      }
      
      // optional int32 organisationId = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_organisationId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &organisationid_)));
          set_has_organisationid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_reference;
        break;
      }
      
      // optional string reference = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_reference:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_reference()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->reference().data(), this->reference().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_wordCount;
        break;
      }
      
      // optional int32 wordCount = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_wordCount:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &wordcount_)));
          set_has_wordcount();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_createdTime;
        break;
      }
      
      // optional string createdTime = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_createdTime:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_createdtime()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->createdtime().data(), this->createdtime().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(82)) goto parse_languageCode;
        break;
      }
      
      // optional string languageCode = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_languageCode:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_languagecode()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->languagecode().data(), this->languagecode().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(90)) goto parse_countryCode;
        break;
      }
      
      // optional string countryCode = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_countryCode:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_countrycode()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->countrycode().data(), this->countrycode().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(98)) goto parse_archivedDate;
        break;
      }
      
      // optional string archivedDate = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_archivedDate:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_archiveddate()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->archiveddate().data(), this->archiveddate().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(104)) goto parse_translatorId;
        break;
      }
      
      // optional int32 translatorId = 13;
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_translatorId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &translatorid_)));
          set_has_translatorid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ArchivedProject::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }
  
  // optional string title = 2;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->title(), output);
  }
  
  // optional string description = 3;
  if (has_description()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->description().data(), this->description().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->description(), output);
  }
  
  // optional string impact = 4;
  if (has_impact()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->impact().data(), this->impact().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->impact(), output);
  }
  
  // optional string deadline = 5;
  if (has_deadline()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->deadline().data(), this->deadline().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->deadline(), output);
  }
  
  // optional int32 organisationId = 6;
  if (has_organisationid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->organisationid(), output);
  }
  
  // optional string reference = 7;
  if (has_reference()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->reference().data(), this->reference().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->reference(), output);
  }
  
  // optional int32 wordCount = 8;
  if (has_wordcount()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->wordcount(), output);
  }
  
  // optional string createdTime = 9;
  if (has_createdtime()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->createdtime().data(), this->createdtime().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->createdtime(), output);
  }
  
  // optional string languageCode = 10;
  if (has_languagecode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->languagecode().data(), this->languagecode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      10, this->languagecode(), output);
  }
  
  // optional string countryCode = 11;
  if (has_countrycode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->countrycode().data(), this->countrycode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      11, this->countrycode(), output);
  }
  
  // optional string archivedDate = 12;
  if (has_archiveddate()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->archiveddate().data(), this->archiveddate().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      12, this->archiveddate(), output);
  }
  
  // optional int32 translatorId = 13;
  if (has_translatorid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(13, this->translatorid(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ArchivedProject::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }
  
  // optional string title = 2;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->title(), target);
  }
  
  // optional string description = 3;
  if (has_description()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->description().data(), this->description().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->description(), target);
  }
  
  // optional string impact = 4;
  if (has_impact()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->impact().data(), this->impact().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->impact(), target);
  }
  
  // optional string deadline = 5;
  if (has_deadline()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->deadline().data(), this->deadline().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->deadline(), target);
  }
  
  // optional int32 organisationId = 6;
  if (has_organisationid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->organisationid(), target);
  }
  
  // optional string reference = 7;
  if (has_reference()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->reference().data(), this->reference().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->reference(), target);
  }
  
  // optional int32 wordCount = 8;
  if (has_wordcount()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->wordcount(), target);
  }
  
  // optional string createdTime = 9;
  if (has_createdtime()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->createdtime().data(), this->createdtime().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->createdtime(), target);
  }
  
  // optional string languageCode = 10;
  if (has_languagecode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->languagecode().data(), this->languagecode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        10, this->languagecode(), target);
  }
  
  // optional string countryCode = 11;
  if (has_countrycode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->countrycode().data(), this->countrycode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        11, this->countrycode(), target);
  }
  
  // optional string archivedDate = 12;
  if (has_archiveddate()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->archiveddate().data(), this->archiveddate().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        12, this->archiveddate(), target);
  }
  
  // optional int32 translatorId = 13;
  if (has_translatorid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(13, this->translatorid(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ArchivedProject::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }
    
    // optional string title = 2;
    if (has_title()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->title());
    }
    
    // optional string description = 3;
    if (has_description()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->description());
    }
    
    // optional string impact = 4;
    if (has_impact()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->impact());
    }
    
    // optional string deadline = 5;
    if (has_deadline()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->deadline());
    }
    
    // optional int32 organisationId = 6;
    if (has_organisationid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->organisationid());
    }
    
    // optional string reference = 7;
    if (has_reference()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->reference());
    }
    
    // optional int32 wordCount = 8;
    if (has_wordcount()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->wordcount());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string createdTime = 9;
    if (has_createdtime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->createdtime());
    }
    
    // optional string languageCode = 10;
    if (has_languagecode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->languagecode());
    }
    
    // optional string countryCode = 11;
    if (has_countrycode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->countrycode());
    }
    
    // optional string archivedDate = 12;
    if (has_archiveddate()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->archiveddate());
    }
    
    // optional int32 translatorId = 13;
    if (has_translatorid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->translatorid());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ArchivedProject::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ArchivedProject* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ArchivedProject*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ArchivedProject::MergeFrom(const ArchivedProject& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_title()) {
      set_title(from.title());
    }
    if (from.has_description()) {
      set_description(from.description());
    }
    if (from.has_impact()) {
      set_impact(from.impact());
    }
    if (from.has_deadline()) {
      set_deadline(from.deadline());
    }
    if (from.has_organisationid()) {
      set_organisationid(from.organisationid());
    }
    if (from.has_reference()) {
      set_reference(from.reference());
    }
    if (from.has_wordcount()) {
      set_wordcount(from.wordcount());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_createdtime()) {
      set_createdtime(from.createdtime());
    }
    if (from.has_languagecode()) {
      set_languagecode(from.languagecode());
    }
    if (from.has_countrycode()) {
      set_countrycode(from.countrycode());
    }
    if (from.has_archiveddate()) {
      set_archiveddate(from.archiveddate());
    }
    if (from.has_translatorid()) {
      set_translatorid(from.translatorid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ArchivedProject::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ArchivedProject::CopyFrom(const ArchivedProject& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ArchivedProject::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void ArchivedProject::Swap(ArchivedProject* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(title_, other->title_);
    std::swap(description_, other->description_);
    std::swap(impact_, other->impact_);
    std::swap(deadline_, other->deadline_);
    std::swap(organisationid_, other->organisationid_);
    std::swap(reference_, other->reference_);
    std::swap(wordcount_, other->wordcount_);
    std::swap(createdtime_, other->createdtime_);
    std::swap(languagecode_, other->languagecode_);
    std::swap(countrycode_, other->countrycode_);
    std::swap(archiveddate_, other->archiveddate_);
    std::swap(translatorid_, other->translatorid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ArchivedProject::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ArchivedProject_descriptor_;
  metadata.reflection = ArchivedProject_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
