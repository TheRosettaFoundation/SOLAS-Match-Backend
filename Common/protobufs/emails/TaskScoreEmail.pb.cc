// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TaskScoreEmail.proto

#include "TaskScoreEmail.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {
class TaskScoreEmailDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<TaskScoreEmail> _instance;
} _TaskScoreEmail_default_instance_;
}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
static void InitDefaultsscc_info_TaskScoreEmail_TaskScoreEmail_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::SolasMatch::Common::Protobufs::Emails::_TaskScoreEmail_default_instance_;
    new (ptr) ::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_TaskScoreEmail_TaskScoreEmail_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_TaskScoreEmail_TaskScoreEmail_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_TaskScoreEmail_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_TaskScoreEmail_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_TaskScoreEmail_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_TaskScoreEmail_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail, email_type_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail, body_),
  1,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::SolasMatch::Common::Protobufs::Emails::_TaskScoreEmail_default_instance_),
};

const char descriptor_table_protodef_TaskScoreEmail_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024TaskScoreEmail.proto\022\"SolasMatch.Commo"
  "n.Protobufs.Emails\032\022EmailMessage.proto\"y"
  "\n\016TaskScoreEmail\022Y\n\nemail_type\030\001 \002(\01625.S"
  "olasMatch.Common.Protobufs.Emails.EmailM"
  "essage.Type:\016TaskScoreEmail\022\014\n\004body\030\002 \002("
  "\t"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_TaskScoreEmail_2eproto_deps[1] = {
  &::descriptor_table_EmailMessage_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_TaskScoreEmail_2eproto_sccs[1] = {
  &scc_info_TaskScoreEmail_TaskScoreEmail_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_TaskScoreEmail_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_TaskScoreEmail_2eproto = {
  false, false, descriptor_table_protodef_TaskScoreEmail_2eproto, "TaskScoreEmail.proto", 201,
  &descriptor_table_TaskScoreEmail_2eproto_once, descriptor_table_TaskScoreEmail_2eproto_sccs, descriptor_table_TaskScoreEmail_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_TaskScoreEmail_2eproto::offsets,
  file_level_metadata_TaskScoreEmail_2eproto, 1, file_level_enum_descriptors_TaskScoreEmail_2eproto, file_level_service_descriptors_TaskScoreEmail_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_TaskScoreEmail_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_TaskScoreEmail_2eproto)), true);
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {

// ===================================================================

void TaskScoreEmail::InitAsDefaultInstance() {
}
class TaskScoreEmail::_Internal {
 public:
  using HasBits = decltype(std::declval<TaskScoreEmail>()._has_bits_);
  static void set_has_email_type(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_body(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000003) ^ 0x00000003) != 0;
  }
};

TaskScoreEmail::TaskScoreEmail(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
}
TaskScoreEmail::TaskScoreEmail(const TaskScoreEmail& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  body_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_body()) {
    body_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_body(),
      GetArena());
  }
  email_type_ = from.email_type_;
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
}

void TaskScoreEmail::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_TaskScoreEmail_TaskScoreEmail_2eproto.base);
  body_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  email_type_ = 1;
}

TaskScoreEmail::~TaskScoreEmail() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void TaskScoreEmail::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  body_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void TaskScoreEmail::ArenaDtor(void* object) {
  TaskScoreEmail* _this = reinterpret_cast< TaskScoreEmail* >(object);
  (void)_this;
}
void TaskScoreEmail::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void TaskScoreEmail::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TaskScoreEmail& TaskScoreEmail::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_TaskScoreEmail_TaskScoreEmail_2eproto.base);
  return *internal_default_instance();
}


void TaskScoreEmail::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      body_.ClearNonDefaultToEmpty();
    }
    email_type_ = 1;
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* TaskScoreEmail::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = TaskScoreEmail];
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(val))) {
            _internal_set_email_type(static_cast<::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // required string body = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_body();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "SolasMatch.Common.Protobufs.Emails.TaskScoreEmail.body");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* TaskScoreEmail::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = TaskScoreEmail];
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_email_type(), target);
  }

  // required string body = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_body().data(), static_cast<int>(this->_internal_body().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Emails.TaskScoreEmail.body");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_body(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  return target;
}

size_t TaskScoreEmail::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  size_t total_size = 0;

  if (_internal_has_body()) {
    // required string body = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_body());
  }

  if (_internal_has_email_type()) {
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = TaskScoreEmail];
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_email_type());
  }

  return total_size;
}
size_t TaskScoreEmail::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required string body = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_body());

    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = TaskScoreEmail];
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_email_type());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TaskScoreEmail::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  GOOGLE_DCHECK_NE(&from, this);
  const TaskScoreEmail* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<TaskScoreEmail>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
    MergeFrom(*source);
  }
}

void TaskScoreEmail::MergeFrom(const TaskScoreEmail& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_body(from._internal_body());
    }
    if (cached_has_bits & 0x00000002u) {
      email_type_ = from.email_type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void TaskScoreEmail::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TaskScoreEmail::CopyFrom(const TaskScoreEmail& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Emails.TaskScoreEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TaskScoreEmail::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  return true;
}

void TaskScoreEmail::InternalSwap(TaskScoreEmail* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  body_.Swap(&other->body_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(email_type_, other->email_type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata TaskScoreEmail::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail* Arena::CreateMaybeMessage< ::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail >(Arena* arena) {
  return Arena::CreateMessageInternal< ::SolasMatch::Common::Protobufs::Emails::TaskScoreEmail >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
