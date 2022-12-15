// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserTaskRevokedEmail.proto

#include "UserTaskRevokedEmail.pb.h"

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
class UserTaskRevokedEmailDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<UserTaskRevokedEmail> _instance;
} _UserTaskRevokedEmail_default_instance_;
}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
static void InitDefaultsscc_info_UserTaskRevokedEmail_UserTaskRevokedEmail_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::SolasMatch::Common::Protobufs::Emails::_UserTaskRevokedEmail_default_instance_;
    new (ptr) ::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_UserTaskRevokedEmail_UserTaskRevokedEmail_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_UserTaskRevokedEmail_UserTaskRevokedEmail_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_UserTaskRevokedEmail_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_UserTaskRevokedEmail_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_UserTaskRevokedEmail_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_UserTaskRevokedEmail_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail, email_type_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail, task_id_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail, user_id_),
  2,
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::SolasMatch::Common::Protobufs::Emails::_UserTaskRevokedEmail_default_instance_),
};

const char descriptor_table_protodef_UserTaskRevokedEmail_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\032UserTaskRevokedEmail.proto\022\"SolasMatch"
  ".Common.Protobufs.Emails\032\022EmailMessage.p"
  "roto\"\231\001\n\024UserTaskRevokedEmail\022_\n\nemail_t"
  "ype\030\001 \002(\01625.SolasMatch.Common.Protobufs."
  "Emails.EmailMessage.Type:\024UserTaskRevoke"
  "dEmail\022\017\n\007task_id\030\002 \002(\005\022\017\n\007user_id\030\003 \002(\005"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_UserTaskRevokedEmail_2eproto_deps[1] = {
  &::descriptor_table_EmailMessage_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_UserTaskRevokedEmail_2eproto_sccs[1] = {
  &scc_info_UserTaskRevokedEmail_UserTaskRevokedEmail_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_UserTaskRevokedEmail_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_UserTaskRevokedEmail_2eproto = {
  false, false, descriptor_table_protodef_UserTaskRevokedEmail_2eproto, "UserTaskRevokedEmail.proto", 240,
  &descriptor_table_UserTaskRevokedEmail_2eproto_once, descriptor_table_UserTaskRevokedEmail_2eproto_sccs, descriptor_table_UserTaskRevokedEmail_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_UserTaskRevokedEmail_2eproto::offsets,
  file_level_metadata_UserTaskRevokedEmail_2eproto, 1, file_level_enum_descriptors_UserTaskRevokedEmail_2eproto, file_level_service_descriptors_UserTaskRevokedEmail_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_UserTaskRevokedEmail_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_UserTaskRevokedEmail_2eproto)), true);
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {

// ===================================================================

void UserTaskRevokedEmail::InitAsDefaultInstance() {
}
class UserTaskRevokedEmail::_Internal {
 public:
  using HasBits = decltype(std::declval<UserTaskRevokedEmail>()._has_bits_);
  static void set_has_email_type(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_task_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_user_id(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000007) ^ 0x00000007) != 0;
  }
};

UserTaskRevokedEmail::UserTaskRevokedEmail(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
}
UserTaskRevokedEmail::UserTaskRevokedEmail(const UserTaskRevokedEmail& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&task_id_, &from.task_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&email_type_) -
    reinterpret_cast<char*>(&task_id_)) + sizeof(email_type_));
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
}

void UserTaskRevokedEmail::SharedCtor() {
  ::memset(&task_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&user_id_) -
      reinterpret_cast<char*>(&task_id_)) + sizeof(user_id_));
  email_type_ = 24;
}

UserTaskRevokedEmail::~UserTaskRevokedEmail() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void UserTaskRevokedEmail::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void UserTaskRevokedEmail::ArenaDtor(void* object) {
  UserTaskRevokedEmail* _this = reinterpret_cast< UserTaskRevokedEmail* >(object);
  (void)_this;
}
void UserTaskRevokedEmail::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void UserTaskRevokedEmail::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const UserTaskRevokedEmail& UserTaskRevokedEmail::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_UserTaskRevokedEmail_UserTaskRevokedEmail_2eproto.base);
  return *internal_default_instance();
}


void UserTaskRevokedEmail::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    ::memset(&task_id_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&user_id_) -
        reinterpret_cast<char*>(&task_id_)) + sizeof(user_id_));
    email_type_ = 24;
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* UserTaskRevokedEmail::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserTaskRevokedEmail];
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
      // required int32 task_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_task_id(&has_bits);
          task_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required int32 user_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_user_id(&has_bits);
          user_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* UserTaskRevokedEmail::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserTaskRevokedEmail];
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_email_type(), target);
  }

  // required int32 task_id = 2;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_task_id(), target);
  }

  // required int32 user_id = 3;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_user_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  return target;
}

size_t UserTaskRevokedEmail::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  size_t total_size = 0;

  if (_internal_has_task_id()) {
    // required int32 task_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_task_id());
  }

  if (_internal_has_user_id()) {
    // required int32 user_id = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_user_id());
  }

  if (_internal_has_email_type()) {
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserTaskRevokedEmail];
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_email_type());
  }

  return total_size;
}
size_t UserTaskRevokedEmail::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required int32 task_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_task_id());

    // required int32 user_id = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_user_id());

    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserTaskRevokedEmail];
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

void UserTaskRevokedEmail::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  GOOGLE_DCHECK_NE(&from, this);
  const UserTaskRevokedEmail* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<UserTaskRevokedEmail>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
    MergeFrom(*source);
  }
}

void UserTaskRevokedEmail::MergeFrom(const UserTaskRevokedEmail& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      task_id_ = from.task_id_;
    }
    if (cached_has_bits & 0x00000002u) {
      user_id_ = from.user_id_;
    }
    if (cached_has_bits & 0x00000004u) {
      email_type_ = from.email_type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void UserTaskRevokedEmail::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserTaskRevokedEmail::CopyFrom(const UserTaskRevokedEmail& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Emails.UserTaskRevokedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserTaskRevokedEmail::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  return true;
}

void UserTaskRevokedEmail::InternalSwap(UserTaskRevokedEmail* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(UserTaskRevokedEmail, user_id_)
      + sizeof(UserTaskRevokedEmail::user_id_)
      - PROTOBUF_FIELD_OFFSET(UserTaskRevokedEmail, task_id_)>(
          reinterpret_cast<char*>(&task_id_),
          reinterpret_cast<char*>(&other->task_id_));
  swap(email_type_, other->email_type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata UserTaskRevokedEmail::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail* Arena::CreateMaybeMessage< ::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail >(Arena* arena) {
  return Arena::CreateMessageInternal< ::SolasMatch::Common::Protobufs::Emails::UserTaskRevokedEmail >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
